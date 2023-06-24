## Linking keymap to QMK
```
ln -s .../qmk-keymaps/ploopy .../qmk_firmware/keyboards/ploopyco/trackball/keymaps/kmazurek
```

## Compiling
```
qmk compile -kb ploopyco/trackball -km kmazurek
```

## Flashing
Note: `qmk flash` includes re-compiling the firmware before flashing.
```
qmk flash -kb ploopyco/trackball -km kmazurek
```
