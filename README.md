# stocktop

![](./img/stocktop.png)

A command-line utility for tracking stock prices based on `ncurses`.

## Dependencies

- `make`
- `libcurl`
- `libjson-c`
- `libncurses`

If you want to run the test suite, you'll also need `libcheck`.

## Building 

```bash
$ make && build/stocktop
```

## To Do

- [x] Color highlighting
- [x] Read/write stock symbols to rc file. Allow user to add/remove their own
  symbols
- [ ] Handle mis-spelled or non-existent symbols that return no data (currently
  segfaults!)
- [ ] Provide keystroke to refresh stock data
- [ ] Allow user to sort by each field
