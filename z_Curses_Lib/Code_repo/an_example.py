'''****************************************************************************
* Definitions
****************************************************************************'''
import curses
import note
'''****************************************************************************
* Variable
****************************************************************************'''
win1_shape = (5,10,2,5)


'''****************************************************************************
* Code
****************************************************************************'''
def mainwindow(stdscr):
    # test main window
    stdscr.box('|','-')
    stdscr.addstr(3, 2, "Hello ", curses.A_REVERSE)
    stdscr.addstr("Dang in bat dau o hang 3, cot 2", curses.A_ITALIC)
    stdscr.addstr(4, 2, "Error ", curses.A_REVERSE)
    stdscr.addstr(4,8,"Khi thay doi kich thuoc cua so thi chuong trinh bi tat !!!", curses.A_ITALIC)
    # clear for another purpose
    stdscr.getkey(); stdscr.clear(); stdscr.box('!','~')
    stdscr.refresh()

    # add newwindow into main win
    #newwin(heigh, width, begin row, begin col)
    win1 = curses.newwin(win1_shape[0],win1_shape[1],win1_shape[2],win1_shape[3])
    
    win1.box('|','-')
    win1.addstr(1,1,"Hello how are u")
    win1.refresh()

    # Ket thuc chuong trinh
    # stdscr.refresh()
    stdscr.getkey()


if __name__ == "__main__":
    # Note
    note.note_default_setting()
    input("\n[Press any key to open 'wrapper']\n\n")

    # Start with wrapper.
    curses.wrapper(mainwindow)