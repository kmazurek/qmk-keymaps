## Installation
```
python3 -m pip install --user qmk
```

```
git clone git@github.com:qmk/qmk_firmware.git
```

After cloning QMK, clone this repo like so:
```
git clone git@github.com:kmazurek/qmk-keymap.git {qmk_path}/keyboards/crkbd/keymaps/kmazurek
```

## Env setup
```
qmk env
```

## Compiling
```
qmk compile -kb crkbd -km kmazurek
```

## Flashing
```
qmk flash -kb crkbd -km kmazurek -bl dfu-split-left && qmk flash -kb crkbd -km kmazurek -bl avrdude-split-right
```
