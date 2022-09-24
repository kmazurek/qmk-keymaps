## Installation
```
python3 -m pip install --user qmk
```

## Env setup
```
qmk env
```

## Compiling

### crkbd
```
qmk compile -kb crkbd -km kmazurek
```

## Flashing

### crkbd
```
qmk flash -kb crkbd -km kmazurek -bl dfu-split-left && qmk flash -kb crkbd -km kmazurek -bl avrdude-split-right
```
