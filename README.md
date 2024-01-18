# MySHAKE128

This is a C implementation of the extendable-output function SHAKE128 following the specification defined in [FIPS 202](https://csrc.nist.gov/pubs/fips/202/final).

## Initialization

Simply use make in the root directory to build the project.

```bash
make
```

## Usage

To run the program run:
```bash
./shake128 32 < short-text.txt
```

The output value shoulb be:
```bash
ba27cc6a7a85887a1888c0678c05cd7fcf619ed791dce41b7e1a81c280bec8bb
```

### Author
Octave Charrin