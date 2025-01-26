# Description

The structure of the Python script, that is converting from different formats to GGUF.

# Structure

## Overall structure of the code
main() ->

## Imports
### Internal dependencies
Standard functionality with:
    - logging
    - argparse
    - ast (metaprogramming can be used instead)
    - json (std.json or asdf for performance)
    - os
    - re
    - sys
    - pathlib
    - hashlib (sha256 from digest module or external libraries)
    - itertools (chain from ranges)

contextlib that using context managers for `with` statements:
is not available in D lang, but the functionality can be simulated

### External dependencies
numpy - D has similar functionlaity in the Mir library
torch - C++ library libtorch can be linked to D code
gguf - C library can be imported through ImportC
safetensors - using safe_open function (259 branch with C API)
transformers - using AutoTokenizer (maybe tokenizers will be enough for that)
sentencepiece - using SentencePieceProcessor (only through C++ API)

## Classes
Model:
    the class is using different parameters from GGUF
    `part_names` field is based on `get_model_part_names` class method with safetensors support, otherwise there is used pytorch's model with .bin
    `hparams` field is based on `load_hparams` class method
    `block_count` is based on `find_hparam` method

## Independent functions
main():
    parsing arguments
    checking registered models from Model class
    init logger
    init `ftype_map` dict with types
    load `hparams` from Model
    with torch.inference_mode init model_class based on architecture
    from `model_class` init `model_instance` based on parameters
    write `vocab` if required, otherwise export the model through `model_instance`
    `get_tensors` is important function, which is using `LazyTorchTensor` class

LazyTorchtensor:


## References/Links
### Torch
* https://github.com/LaurentMazare/tch-rs (use C API for torch from gen)

### SafeTensors
* https://github.com/huggingface/safetensors/tree/c_bindings/bindings/c (branch with C API)

### SentencePiece
* https://formulae.brew.sh/formula/sentencepiece (macOS installation)
* https://github.com/google/sentencepiece/blob/master/doc/api.md (examples)