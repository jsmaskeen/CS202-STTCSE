import subprocess
import json
import csv
from collections import defaultdict

def dot2png(dot_filename, png_filename):
    command = ["dot", "-Tpng", dot_filename, "-o", f"{png_filename}.png"]
    subprocess.run(command, check=True, capture_output=True, text=True)
    print(f"Image saved to {png_filename}.png")


def find_multiple_reaching_definitions(definitions_file, iterations_file, use_field='in[B]'):
    try:
        with open(definitions_file, 'r') as f:
            definitions = json.load(f)
    except FileNotFoundError:
        raise FileNotFoundError(f"Definitions file not found: {definitions_file}")
    def_to_var = {}
    for def_id, data in definitions.items():
        if isinstance(data, (list, tuple)) and data:
            def_to_var[str(def_id)] = data[0]
        else:
            def_to_var[str(def_id)] = str(data)

    try:
        with open(iterations_file, 'r', newline='') as f:
            reader = csv.DictReader(f)
            if reader.fieldnames:
                reader.fieldnames = [name.strip() for name in reader.fieldnames]
            rows = list(reader)
    except FileNotFoundError:
        raise FileNotFoundError(f"Iterations file not found: {iterations_file}")
    except Exception as e:
        raise RuntimeError(f"Error reading CSV: {e}")

    if not rows:
        return {}

    try:
        last_iteration = max(int(r['Iteration']) for r in rows if r.get('Iteration') not in (None, ''))
    except Exception:
        last_iteration = max(r.get('Iteration') for r in rows)
    final_rows = [r for r in rows if str(r.get('Iteration')) == str(last_iteration)]

    results = {} 
    for row in final_rows:
        block_name = row.get('Basic-Block', '').strip() or '<unknown>'
        raw_field = row.get(use_field, '[]')
        if raw_field is None:
            raw_field = '[]'
        try:
            in_defs = eval(raw_field.strip())
            if not isinstance(in_defs, (list, tuple)):
                in_defs = [in_defs]
        except (ValueError, SyntaxError):
            s = str(raw_field).strip()
            if s.startswith('[') and s.endswith(']'):
                s = s[1:-1].strip()
            in_defs = [t.strip().strip("'\"") for t in s.split(',') if t.strip()]

        vars_in_block = defaultdict(list)
        for def_id in in_defs:
            if def_id is None:
                continue
            def_id_str = str(def_id).strip().strip("'\"")
            var = def_to_var.get(def_id_str)
            if var:
                vars_in_block[var].append(def_id_str)
        for var, def_list in vars_in_block.items():
            seen = []
            for d in def_list:
                if d not in seen:
                    seen.append(d)
            if len(seen) > 1:
                results.setdefault(block_name, {})[var] = seen

    return results