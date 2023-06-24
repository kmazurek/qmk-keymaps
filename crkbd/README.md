## Linking keymap to QMK
```
ln -s .../qmk-keymaps/crkbd .../qmk_firmware/keyboards/crkbd/keymaps/kmazurek
```

## Compiling
```
qmk compile -kb crkbd -km kmazurek
```

## Flashing
Note: `qmk flash` includes re-compiling the firmware before flashing.
```
qmk flash -kb crkbd -km kmazurek -bl dfu-split-left && qmk flash -kb crkbd -km kmazurek -bl avrdude-split-right
```
