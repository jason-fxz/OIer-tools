# Compile & Run .cpp files

The Shell Script [R.sh](./R.sh)

## Usage

```bash
./R.sh <FileBaseName> [FlagsType]
```

For *FlagsType* :

- `debug` (default)
- `O2`
- `O3`
- `Ofast`
- `empty`

For example, your file is `hello world.cpp`, use :

```bash
./R.sh 'hello world'
```

It compiles `hello world.cpp` into `hello world.run`

It checks whether the file has been modified, if not, run without compiling (file `.hello world.cpp.bak` will be created to check modification)

## More

For convenience, you can copy `R.sh` to `~/R.sh`, and add an alias in `~/.bashrc`

```bash
alias R='~/R.sh'
```

Then you can use the flowing command instead.

```bash
R 'hello world'
```
