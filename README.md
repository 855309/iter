# iter
Complex iteration renderer.

```bash
Usage:
./iter [colormap_file] [start_w] [c.re] [c.im] [iterations] [img_w] [img_h] [out_path] [threads] [zoom / apply_ei] [fac_start] [fac_end] [steps (frames)]
```
## Examples

#### ``f(z) = z^2 + 0.7885*e^iy``

![img1](img/jl1.gif)

Generated from the output of:
```bash
./iter "colormaps/jet.txt" 2.3 0 0 jul 0.7885 0 81 620 400 render 4 apply_ei 0 2 1200
```

#### ``f(z) = z^2 + 0.7885i``

![img2](img/jl2.png)

From:
```bash
./iter colormaps/turbo.txt 2.5 0 0 jul 0 0.7885 100 1366 768 render 4 apply_ei 0 0 1
```
