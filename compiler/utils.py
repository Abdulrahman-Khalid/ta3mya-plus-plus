from tkinter import filedialog, messagebox
import tkinter as tk
import os

ERR_MSG = "Compilation Failed"

class PrintLogger():  # create file like object
    def __init__(self, textbox):  # pass reference to text widget
        self.textbox = textbox  # keep ref
        self.isError = False

    def write(self, text):
        self.textbox.delete("1.0", tk.END)
        self.textbox.config(state=tk.NORMAL)
        if(text.startswith(ERR_MSG)):
            self.isError = True
            self.textbox.insert(tk.END, text, "error")
        else:
            if(self.isError):
                self.textbox.insert(tk.END, text, "error")
            else:
                self.textbox.insert(tk.END, text, "normal")
            self.isError = False
        self.textbox.config(state=tk.DISABLED)
        # could also scroll to end of textbox here to make sure always visible

    def flush(self):  # needed for file like object
        pass


def saveFile(text):
    t = text.get("1.0", tk.END+"-1c")
    savelocation = filedialog.asksaveasfile(initialdir="./", title="Select file", filetypes=((("Program Files", ".ta3"),("all files", "*.*"))))
    if (savelocation):
        savelocation.write(t)
        savelocation.close()
        return True
    return False


def newFile(text):
    if (len(text.get("1.0", tk.END+"-1c")) > 0):
        if(messagebox.askyesno("Save File", "Do you want to save your file before making new one?")):
            if(saveFile(text)):
                text.delete("1.0", tk.END)
        else:
            text.delete("1.0", tk.END)


def openFile(root, text):
    openLocation = filedialog.askopenfile(initialdir="./", title="Select file", filetypes=(( ("Program Files", ".ta3"), ("all files", "*.*") )) )
    root.title(os.path.basename(openLocation.name) + " _ Ta3mya Compiler")
    if(openLocation):
        text.delete('1.0', tk.END)
        text.insert('1.0', openLocation.read())

def exitRoot(root):
    if messagebox.askyesno("Exit", "Are you sure you want to exit ?"):
        root.destroy()


def showAbout():
    messagebox.showinfo(
        "About", "Ta3mya V1.0.0")


def showHelp():
    messagebox.showinfo(
        "Help", "1. Write or open your program in ta3mya++\n2.Click compile")

def chooseProgDirectory(assemblerObj):
    progLocation = tk.filedialog.askdirectory(
        initialdir="./", title="Select debug file directory")

    if(progLocation):
        assemblerObj.setDebugFile(progLocation+"/debug.txt")
        assemblerObj.setProgFile(progLocation+"/program.asm")