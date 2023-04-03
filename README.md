# MikuAR

PlayStation Vita plugin to enable running `PCSC90032` at any date or time.

Made by Avellea

# Building
```bash
$ mkdir build
$ cd build
$ cmake ../
$ make
```

# Installing
This requires a specific image for the AR to work. I'll update this when I find a good image.

Place the following at the bottom of `ur0:tai/config.txt`
```
*PCSC90032
ur0:tai/mikuar.suprx
```

# Credits
[SonicMastr](https://github.com/SonicMastr) - Help with development

[Null-39](https://github.com/Null-39) - Testing