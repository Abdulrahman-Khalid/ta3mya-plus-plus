from tkinter import filedialog, messagebox
import tkinter as tk
import os

SUCCESS = "Compiled Successfully"
ERR_MSG = "Compilation Failed"
ERR_MSG_LINE = "Error"
WARN_MSG = "Warning"

class PrintLogger():  # create file like object
    def __init__(self, textbox):  # pass reference to text widget
        self.textbox = textbox  # keep ref

    def write(self, text):
        self.textbox.config(state=tk.NORMAL)
        if(text.startswith(SUCCESS)):
            self.textbox.insert(tk.END, text, "success")
        elif(text.startswith(ERR_MSG) or text.startswith(ERR_MSG_LINE)):
            self.textbox.insert(tk.END, text, "error")
        elif(text.startswith(WARN_MSG)):
            self.textbox.insert(tk.END, text, "warning")
        else:
            self.textbox.insert(tk.END, text, "normal")
        self.textbox.config(state=tk.DISABLED)
        # could also scroll to end of textbox here to make sure always visible

    def flush(self):  # needed for file like object
        pass


def saveFile(text):
    t = text.get("1.0", tk.END+"-1c")
    savelocation = filedialog.asksaveasfile(initialdir="./", title="Select file", filetypes=((("Program Files", ".ta"),("all files", "*.*"))))
    if (savelocation):
        savelocation.write(t)
        savelocation.close()
        return True
    return False


def newFile(text, console):
    console.config(state=tk.NORMAL)
    console.delete("1.0", tk.END)
    console.config(state=tk.DISABLED)
    if (len(text.get("1.0", tk.END+"-1c")) > 0):
        if(messagebox.askyesno("Save File", "Do you want to save your file before making new one?")):
            if(saveFile(text)):
                text.delete("1.0", tk.END)
        else:
            text.delete("1.0", tk.END)


def openFile(root, text, console):
    openLocation = filedialog.askopenfile(initialdir="./", title="Select file", filetypes=(( ("Program Files", ".ta"), ("all files", "*.*") )) )
    if(openLocation):
        root.title(os.path.basename(openLocation.name) + " _ Ta3mya Compiler")
        text.delete('1.0', tk.END)
        text.insert('1.0', openLocation.read())
        console.config(state=tk.NORMAL)
        console.delete("1.0", tk.END)
        console.config(state=tk.DISABLED)


def exitRoot(root):
    if messagebox.askyesno("Exit", "Are you sure you want to exit ?"):
        root.destroy()


def showAbout():
    messagebox.showinfo(
        "About", "Ta3mya V1.0.0")


def showHelp():
    messagebox.showinfo(
        "Help", "1. Write or open your program in ta3mya++ language\n2. Click compile")

def chooseProgDirectory(compilerObj):
    progLocation = tk.filedialog.askdirectory(
        initialdir="./", title="Select Compilation Directory")

    if(progLocation):
        compilerObj.setDebugFile(progLocation+"/Debug.txt")
        compilerObj.setProgFile(progLocation+"/Program.asm")
        compilerObj.setSymbolTableFile(progLocation+"/SymbolTable.txt")