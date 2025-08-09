import os
import shutil
import yaml


def main():
  base_dir = os.path.dirname(os.path.abspath(__file__))
  pgns_dir = os.path.abspath(os.path.join(base_dir, '..', 'pgns'))
  gen_pgns_dir = os.path.abspath(os.path.join(base_dir, '..', '_pgns'))

  # Ensure the gen pgns directory exists or is cleaned up
  if os.path.exists(gen_pgns_dir):
    for filename in os.listdir(gen_pgns_dir):
      file_path = os.path.join(gen_pgns_dir, filename)
      if os.path.isfile(file_path) or os.path.islink(file_path):
        os.unlink(file_path)
      elif os.path.isdir(file_path):
        shutil.rmtree(file_path)
  else:
    os.makedirs(gen_pgns_dir)

  for filename in os.listdir(pgns_dir):
    if not filename.endswith('.yaml'):
      continue
  
    # read the YAML file
    with open(os.path.join(pgns_dir, filename), 'r') as fin:
      pgn = yaml.safe_load(fin)

    # generate hpp file
    fields = []
    for field in pgn["fields"]:
      if field["type"] == "reserved":
        continue
      fields.append(f'  {field["type"]} {field["name"]};')
    
    get_fields = []
    for field in pgn["fields"]:
      if field["type"] == "reserved":
        get_fields.append(f'    bit_idx += {field["bitsize"]}; // skip reserved')
      elif field["type"] == "double":
        get_fields.append(f'    {field["name"]} = static_cast<{"int64_t" if field["signed"] else "uint64_t"}>(data.get_bits_and_increment<{field["bitsize"]}>(bit_idx)) * {field["scale"]};')
      else:
        get_fields.append(f'    {field["name"]} = data.get_bits_and_increment<{field["bitsize"]}>(bit_idx);')

    lines = [
      f'#include <packet.hpp>',
      f'',
      f'namespace n2k::pgns',
      f'{{',
      f'',
      f'struct {pgn["name"]}',
      f'{{',
      f'  static constexpr uint32_t PGN = {hex(pgn["pgn"])};',
      f'',
      *fields,
      f'',
      f'  {pgn["name"]}(const can::PayloadData & data)',
      f'  {{',
      f'    std::size_t bit_idx = 0;',
      *get_fields,
      f'  }}',
      f'}};',
      f'',
      f'}} // namespace n2k::pgns',
      f''
    ]

    # Write the generated lines to the header file
    with open(os.path.join(gen_pgns_dir, f'{pgn["name"]}.hpp'), 'w') as fout:
      fout.write('\n'.join(lines))


if __name__ == '__main__':
  main()
