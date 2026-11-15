# evdev-dump

Minimal C utility to dump raw Linux input events (`EV_KEY`, `MSC_SCAN`, etc.) from `/dev/input/eventX`.

## Build

```bash
gcc -O2 -Wall -o evdev-dump main.c
```

## Usage

Requires root or `input` group permissions:

```bash
sudo ./evdev-dump [device]
```

Defaults to `/dev/input/event3` if no device is specified:

```bash
sudo ./evdev-dump /dev/input/event5
```

## Example Output

```text
Listening on /dev/input/event3 ...
EV_MSC MSC_SCAN scan code=0x1e
EV_KEY code=0x1e value=1
type=0 code=0 value=0
```
* `value`: `1` = press, `0` = release, `2` = repeat
* `type=0`: `EV_SYN` (sync report)
