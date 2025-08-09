# N2K Library

This library provides support for NMEA 2000 (N2K) Parameter Group Numbers (PGNs) with automatic C++ struct generation from YAML definitions.

## Adding New PGNs

To add support for a new PGN, create a YAML file in the `pgns/` directory. The YAML file will automatically generate a corresponding C++ struct that can be used to parse N2K data.

### YAML Format

Each YAML file should follow this structure:

```yaml
name: pgn_name
pgn: 0x12345
description: "Human readable description"

fields:
  - name: field_name
    type: uint8_t|uint16_t|uint32_t|int8_t|int16_t|int32_t
    bitsize: 8
    description: "Field description"

  - name: scaled_field
    type: double
    bitsize: 16
    signed: true
    scale: 0.01
    unit: "m"
    description: "Field with scaling factor"

  - name: reserved
    type: reserved
    bitsize: 8
```

See [canboat.github.io](https://canboat.github.io/canboat/canboat.html) for most common PGN formats.

### Example

See the existing YAML files:
- `pgns/WaterDepth.yaml` - Water depth measurements
- `pgns/WindData.yaml` - Wind speed and direction data
