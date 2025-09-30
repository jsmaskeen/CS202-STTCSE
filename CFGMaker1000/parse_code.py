import re


def get_main_function_contents(code):
    main_code = re.search(r"int main\(void\)\n\{((.*\n)+)}", code, re.DOTALL).group(1)
    main_code_lines = [
        i.strip() for i in main_code.replace("\n\n", "\n").split("\n") if i != ""
    ]
    return main_code_lines


def parse_code(lines, start_index=0):
    nodes = []
    i = start_index
    while i < len(lines):
        line = lines[i].strip() if i < len(lines) else ""

        if not line:
            i += 1
            continue

        if line.startswith("if"):
            condition_match = re.search(r"\((.*)\)", line)
            condition = condition_match.group(1) if condition_match else ""

            # Check for block body vs. single-statement body
            if i + 1 < len(lines) and lines[i + 1].strip() == "{":
                body_nodes, end_index = parse_code(lines, i + 2)
            else:  # Single-statement body
                body_nodes = [{"type": "statement", "code": lines[i + 1].strip()}]
                end_index = i + 1

            if_chain_root = {"type": "if", "condition": condition, "body": body_nodes}
            nodes.append(if_chain_root)

            current_clause = if_chain_root
            current_end_index = end_index

            while True:
                next_line_index = current_end_index + 1
                if next_line_index >= len(lines):
                    break
                next_line = lines[next_line_index].strip()

                if next_line.startswith("else if"):
                    condition_match = re.search(r"\((.*)\)", next_line)
                    condition = condition_match.group(1) if condition_match else ""

                    if (
                        next_line_index + 1 < len(lines)
                        and lines[next_line_index + 1].strip() == "{"
                    ):
                        body_nodes, end_index = parse_code(lines, next_line_index + 2)
                    else:  # Single-statement else if
                        body_nodes = [
                            {
                                "type": "statement",
                                "code": lines[next_line_index + 1].strip(),
                            }
                        ]
                        end_index = next_line_index + 1

                    else_if_node = {
                        "type": "if",
                        "condition": condition,
                        "body": body_nodes,
                    }
                    current_clause["else_body"] = [else_if_node]
                    current_clause = else_if_node
                    current_end_index = end_index

                elif next_line.startswith("else"):
                    if (
                        next_line_index + 1 < len(lines)
                        and lines[next_line_index + 1].strip() == "{"
                    ):
                        body_nodes, end_index = parse_code(lines, next_line_index + 2)
                    else:  # Single-statement else
                        body_nodes = [
                            {
                                "type": "statement",
                                "code": lines[next_line_index + 1].strip(),
                            }
                        ]
                        end_index = next_line_index + 1

                    current_clause["else_body"] = body_nodes
                    current_end_index = end_index
                    break
                else:
                    break

            i = current_end_index + 1

        elif line.startswith(("for", "while")):
            if line.startswith("for"):
                condition_match = re.search(r"\((.*);(.*);(.*)\)", line)
                if condition_match:
                    initialization = condition_match.group(1).strip()
                    condition = condition_match.group(2).strip()
                    increment = condition_match.group(3).strip()
                else:
                    initialization, condition, increment = "", "", ""
            else: # while loop
                condition_match = re.search(r"\((.*)\)", line)
                condition = condition_match.group(1) if condition_match else ""
                initialization, increment = None, None
                
            # Check for block body vs. single-statement body
            if i + 1 < len(lines) and lines[i + 1].strip() == "{":
                body_nodes, end_index = parse_code(lines, i + 2)
                i = end_index + 1
            else:  # Single-statement body
                body_nodes = [{"type": "statement", "code": lines[i + 1].strip()}]
                i = i + 2  # Move past the loop and the single statement

            block = {
                "type": "loop",
                "condition": condition,
                "body": body_nodes,
                "loop_type": "for" if line.startswith("for") else "while",
            }

            if initialization:
                block['initialization'] = initialization
            if increment:
                block['increment'] = increment

            nodes.append(block)

        elif line == "}":
            return nodes, i

        elif line and line not in ["{"] and not line.startswith(("else if", "else")):
            nodes.append({"type": "statement", "code": line})
            i += 1
        else:
            i += 1

    return nodes, i

