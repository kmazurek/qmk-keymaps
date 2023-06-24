## QMK installation
```
python3 -m pip install --user qmk
```

```
git clone git@github.com:qmk/qmk_firmware.git
```

## Env setup
```
qmk env
```

## Updating the repo
```
git pull --recurse-submodules
```

## Keymap importing
After cloning the QMK main repository, use symlinking and flashing instructions in each of the hardware sub-directories of this repo.

## Debugging
After compiling firmware with some prints you can connect to the device by running:
```
qmk console
```
