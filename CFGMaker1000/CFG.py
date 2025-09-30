import re
import csv
import json

class BasicBlock:
    def __init__(self, name):
        self.name = name
        self.instructions = []
        self.successors = []
        self.gen = set()
        self.kill = set()
        self.in_defs = set()
        self.out_defs = set()

    def add_instruction(self, instruction):
        self.instructions.append(instruction)

    def add_successor(self, block, label=None):
        if any(succ == block for succ, _ in self.successors):
            return
        self.successors.append((block, label))


class ControlFlowGraph:
    def __init__(self):
        self.blocks = {}
        self.start_block = None
        self._block_counter = 0
        self.definitions = {}  # Maps def ID ('D1') to (variable, code)
        self.var_to_defs = {}
        self._def_counter = 1
        self.iteration_history = []

    def get_new_block_name(self):
        name = f"B{self._block_counter}"
        self._block_counter += 1
        return name

    def create_block(self):
        name = self.get_new_block_name()
        block = BasicBlock(name)
        self.blocks[name] = block
        if self.start_block is None:
            self.start_block = block
        return block

    def build(self, code_structure):
        self._build_recursive(code_structure, None)

    def _build_recursive(self, instructions, current_block):
        if not instructions:
            return current_block
        if current_block is None:
            current_block = self.create_block()

        for instruction in instructions:
            instr_type = instruction.get("type")

            if instr_type == "statement":
                current_block.add_instruction(instruction["code"])

            elif instr_type == "if":
                if current_block.instructions:
                    prev_block = current_block
                    current_block = self.create_block()
                    prev_block.add_successor(current_block)

                current_block.add_instruction(f"if ({instruction['condition']})")

                if_block = self.create_block()
                current_block.add_successor(if_block, label="true")
                last_if_block = self._build_recursive(
                    instruction.get("body", []), if_block
                )

                after_if_block = self.create_block()
                if last_if_block:
                    last_if_block.add_successor(after_if_block)

                if "else_body" in instruction:
                    else_block = self.create_block()
                    current_block.add_successor(else_block, label="false")
                    last_else_block = self._build_recursive(
                        instruction["else_body"], else_block
                    )
                    if last_else_block:
                        last_else_block.add_successor(after_if_block)
                else:
                    current_block.add_successor(after_if_block, label="false")

                current_block = after_if_block

            elif instr_type == "loop":
                if current_block.instructions:
                    prev_block = current_block
                    current_block = self.create_block()
                    prev_block.add_successor(current_block)

                loop_condition_block = current_block
                loop_condition_block.add_instruction(
                    f"{instruction.get('loop_type', 'loop')} ({instruction['condition']})"
                )

                loop_body_block = self.create_block()
                loop_condition_block.add_successor(loop_body_block, label="true")
                last_loop_body_block = self._build_recursive(
                    instruction.get("body", []), loop_body_block
                )
                if last_loop_body_block:
                    last_loop_body_block.add_successor(loop_condition_block)

                after_loop_block = self.create_block()
                loop_condition_block.add_successor(after_loop_block, label="false")
                current_block = after_loop_block

        return current_block

    def analyze_definitions(self, code_structure):
        self._find_all_definitions(code_structure)
        if not self.definitions:
            print("No definitions found.")
            return
        self._compute_gen_kill()
        self._compute_reaching_definitions()

    def _find_all_definitions(self, instructions):
        for instr in instructions:
            if instr["type"] == "statement":
                code = instr["code"]
                match = re.match(
                    r"\s*(?:[\w\s]+\s+)?\*?(\w+)\s*\[?.*?]?\s*=\s*.+;", code
                )
                if match:
                    var_name = match.group(1)
                    def_id = f"D{self._def_counter}"
                    self.definitions[def_id] = (var_name, code)
                    if var_name not in self.var_to_defs:
                        self.var_to_defs[var_name] = set()
                    self.var_to_defs[var_name].add(def_id)
                    self._def_counter += 1
            elif instr["type"] in ["if", "loop"]:
                if "body" in instr:
                    self._find_all_definitions(instr["body"])
                if "else_body" in instr:
                    self._find_all_definitions(instr["else_body"])

    # def _compute_gen_kill(self):
    #     """Computes the gen and kill sets for every basic block."""
    #     code_to_def_id = {code: did for did, (_, code) in self.definitions.items()}
    #     for block in self.blocks.values():
    #         block.gen.clear()
    #         block.kill.clear()
    #         for instr_code in block.instructions:
    #             if instr_code in code_to_def_id:
    #                 def_id = code_to_def_id[instr_code]
    #                 var_name, _ = self.definitions[def_id]
    #                 block.gen.add(def_id)
    #                 other_defs = self.var_to_defs[var_name] - {def_id}
    #                 block.kill.update(other_defs)

    def _compute_gen_kill(self):
        code_to_def_id = {code: did for did, (_, code) in self.definitions.items()}

        for block in self.blocks.values():
            block.gen.clear()
            block.kill.clear()
            locally_generated = {}

            for instr_code in block.instructions:
                if instr_code in code_to_def_id:
                    def_id = code_to_def_id[instr_code]
                    var_name, _ = self.definitions[def_id]

                    other_defs_for_var = self.var_to_defs.get(var_name, set())
                    block.kill.update(other_defs_for_var)

                    locally_generated[var_name] = def_id

            block.gen = set(locally_generated.values())
            block.kill = block.kill - block.gen

    def _compute_reaching_definitions(self):
        for block in self.blocks.values():
            block.in_defs = set()
            block.out_defs = set()

        changed = True
        while changed:
            current_iteration_data = {}
            for name, block in self.blocks.items():
                current_iteration_data[name] = {
                    "in": set(block.in_defs),
                    "out": set(block.out_defs),
                }
            self.iteration_history.append(current_iteration_data)
            changed = False
            predecessors = {name: [] for name in self.blocks}
            for name, block in self.blocks.items():
                for succ, _ in block.successors:
                    predecessors[succ.name].append(name)

            for name, block in sorted(
                self.blocks.items(), key=lambda item: int(item[0][1:])
            ):
                new_in = set()
                for pred_name in predecessors[name]:
                    new_in.update(self.blocks[pred_name].out_defs)
                block.in_defs = new_in

                old_out = block.out_defs
                new_out = block.gen.union(block.in_defs - block.kill)

                if new_out != old_out:
                    block.out_defs = new_out
                    changed = True

            final_iteration_data = {}
            for name, block in self.blocks.items():
                final_iteration_data[name] = {
                    "in": set(block.in_defs),
                    "out": set(block.out_defs),
                }
            self.iteration_history.append(final_iteration_data)

    def export_analysis_results(self, filename_base):
        if not self.definitions:
            return

        def_map_filename = f"{filename_base}_definitions.json"
        try:
            with open(def_map_filename, "w") as f:
                sorted_defs = {
                    k: self.definitions[k]
                    for k in sorted(self.definitions.keys(), key=lambda d: int(d[1:]))
                }
                json.dump(sorted_defs, f, indent=4)
            print(f"Definition map saved to {def_map_filename}")
        except Exception as e:
            print(f"Error saving definition map: {e}")

        csv_filename = f"{filename_base}_reaching_definitions_iterations.csv"
        try:
            with open(csv_filename, "w", newline="") as f:
                writer = csv.writer(f)
                writer.writerow(
                    ["Iteration", "Basic-Block", "gen[B]", "kill[B]", "in[B]", "out[B]"]
                )

                for i, iteration_data in enumerate(self.iteration_history):
                    iteration_num = i
                    for name, data in sorted(
                        iteration_data.items(), key=lambda item: int(item[0][1:])
                    ):
                        block = self.blocks[name]
                        gen_str = str(sorted(list(block.gen)))
                        kill_str = str(sorted(list(block.kill)))
                        in_str = str(sorted(list(data["in"])))
                        out_str = str(sorted(list(data["out"])))
                        writer.writerow(
                            [iteration_num, name, gen_str, kill_str, in_str, out_str]
                        )
            print(
                f"Reaching definitions analysis (all iterations) saved to {csv_filename}"
            )
        except Exception as e:
            print(f"Error saving analysis CSV: {e}")

    def cc(self):
        E = sum(len(block.successors) for block in self.blocks.values())
        N = len(self.blocks)
        return E - N + 2

    def visualize(self, filename):
        dot_source = [
            "digraph ControlFlowGraph {",
            '    node [shape=box, fontname="Courier"];',
            '    edge [fontname="Helvetica"];',
        ]

        for name, block in self.blocks.items():
            instructions_str = (
                "\\l".join(
                    i.replace("\\", "\\\\")
                    .replace('"', '\\"')
                    .replace("{", "\\{")
                    .replace("}", "\\}")
                    for i in block.instructions
                )
                + "\\l"
            )

            label = f'"{name}\\n\\l{instructions_str}"'
            dot_source.append(f"    {name} [label={label}];")

        for name, block in self.blocks.items():
            for successor, label in block.successors:
                edge = f"    {name} -> {successor.name}"
                if label:
                    edge += f' [label="{label}"]'
                edge += ";"
                dot_source.append(edge)

        dot_source.append("}")
        dot_content = "\n".join(dot_source)
        dot_filepath = f"{filename}.dot"

        try:
            with open(dot_filepath, "w") as f:
                f.write(dot_content)
            print(f"CFG source saved to {dot_filepath}")
        except Exception as e:
            print(f"An unexpected error occurred: {e}")
