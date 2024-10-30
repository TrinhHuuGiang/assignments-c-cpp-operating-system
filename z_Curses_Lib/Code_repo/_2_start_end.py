#example debug with wrapper
#if not using wrapper, the error may be not display right

import curses
from curses import wrapper

def main(stdscr):
    #stdscr is an object control screen
    # Xóa màn hình
    stdscr.clear()

    # Tạo lỗi ZeroDivisionError khi i == 10
    for i in range(0, 11):
        v = i - 10
        stdscr.addstr(i, 0, '10 chia cho {} là {}'.format(v, 10 / v))

    #update
    stdscr.refresh()

    #wait to any key
    stdscr.getkey()

wrapper(main) #with default is noecho(), cbreak(), keypad(True)