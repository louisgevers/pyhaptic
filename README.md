# pyhaptic
Unofficial Python bindings for Force Dimension Haptic SDK.

## Installation

Clone the repository and its submodules:

```bash
$ git clone --recurse-submodules
```

Download the [Force Dimension SDK](https://www.forcedimension.com/software/sdk).
To install pyhaptic with the SDK, you have two options:

**(a) Environment variable**

Point the `FORCE_DIMENSION_SDK` variable to the SDK's path:

```$ export FORCE_DIMENSION_SDK=/path/to/sdk```

**(b) Move the SDK**

Move the SDK folder under [src/dhd/include](src/dhd/include) (and rename the folder to `force-dimension-sdk`).
The structure should look as follows:

```
- src
    - dhd
        - include
            - force-dimension-sdk
                - bin
                - doc
                - examples
                - ...
```

Once you have done either **(a)** or **(b)**, install pyhaptic in your environment of choice, this will create the bindings and interface under the `pyhaptic` module (and raw bindings under `pyhaptic.dhd`).

```bash
$ pip install .
```

## Basic usage

After connecting a haptic device, use the `Device` class of `pyhaptic` to establish a connection and interact with the device.
Each `Device` will attempt to open the connection on creation and throw a `ConnectionError` if this fails. For multiple devices, just create multiple `Device` objects.

```python
import pyhaptic

# Connect with the device
device = pyhaptic.Device()

# Read its position
px, py, pz = device.get_position()

# Close the connection
device.close()
```

See [examples/springmodel.py](examples/springmodel.py) for an easy implementation to test your installation.