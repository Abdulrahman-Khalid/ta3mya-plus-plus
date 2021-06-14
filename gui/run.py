import utils
import tkinter as tk
import os
import sys
from subprocess import Popen, PIPE

def compileOnly(gui, compiler):
    console = gui.getConsoleArea()
    console.config(state=tk.NORMAL)
    console.delete("1.0", tk.END)
    console.config(state=tk.DISABLED)

    content = gui.getTextArea().get("1.0", tk.END+"-1c")
    with Popen(compiler.getCompilerExe(), stdin=PIPE, stdout=PIPE, stderr=PIPE, shell=True) as process:
        process.stdin.write(str.encode(content))
        assemblyOutput = process.communicate()[0].decode("utf-8")
        error = process.communicate()[1].decode("utf-8")
        lines = error.splitlines()
        debugList = []
        errorList = []
        warningList = []
        for line in lines:
            lowerLine = line.lower()
            if (lowerLine.startswith("error")):
                errorList.append(line)
            elif (lowerLine.startswith("warning")):
                warningList.append(line)
            else:
                debugList.append(line)
        consoleOut = []
        if (len(errorList) > 0):
            consoleOut.append(utils.ERR_MSG + '\n\n')
            if (len(warningList) > 0):
                consoleOut.append('\n'.join(warningList) + '\n\n')
            consoleOut.append('\n'.join(errorList))
        else:
            consoleOut.append("Compiled Successfully\n\n\n")
            if (len(warningList) > 0):
                consoleOut.append('\n'.join(warningList) + '\n\n')
        for out in consoleOut:
            print(out)
        debugOut = '\n'.join(debugList)
        if (len(debugOut) > 0):
            with open(compiler.getDebugFile(), 'w') as f:
                f.write(debugOut)
        if (len(assemblyOutput) > 0):
            with open(compiler.getProgFile(), 'w') as f:
                f.write(assemblyOutput)
            print("\nCompiled Assembly:\n")
            print(assemblyOutput)

class TextLineNumbers(tk.Canvas):
    def __init__(self, *args, **kwargs):
        tk.Canvas.__init__(self, *args, **kwargs)
        self.textwidget = None

    def attach(self, text_widget):
        self.textwidget = text_widget

    def redraw(self, *args):
        '''redraw line numbers'''
        self.delete("all")

        i = self.textwidget.index("@0,0")
        while True:
            dline = self.textwidget.dlineinfo(i)
            if dline is None:
                break
            y = dline[1]
            linenum = str(i).split(".")[0]
            self.create_text(2, y, anchor="nw", text=linenum)
            i = self.textwidget.index("%s+1line" % i)


class CustomText(tk.Text):
    def __init__(self, *args, **kwargs):
        tk.Text.__init__(self, *args, **kwargs)

        # create a proxy for the underlying widget
        self._orig = self._w + "_orig"
        self.tk.call("rename", self._w, self._orig)
        self.tk.createcommand(self._w, self._proxy)

    def _proxy(self, *args):
        # let the actual widget perform the requested action
        cmd = (self._orig,) + args
        result = self.tk.call(cmd)

        # generate an event if something was added or deleted,
        # or the cursor position changed
        if (args[0] in ("insert", "replace", "delete") or
                    args[0:3] == ("mark", "set", "insert") or
                    args[0:2] == ("xview", "moveto") or
                    args[0:2] == ("xview", "scroll") or
                    args[0:2] == ("yview", "moveto") or
                    args[0:2] == ("yview", "scroll")
                ):
            self.event_generate("<<Change>>", when="tail")

        # return what the actual widget returned
        return result


class GUI(tk.Frame):
    def __init__(self, *args, **kwargs):
        tk.Frame.__init__(self, *args, **kwargs)
        self.text = CustomText(self)
        self.vsb = tk.Scrollbar(orient="vertical", command=self.text.yview)
        self.text.configure(yscrollcommand=self.vsb.set,
                            font=("Helvetica", "14", "bold"))
        self.linenumbers = TextLineNumbers(self, width=20)
        self.linenumbers.attach(self.text)

        self.vsb.pack(side="right", fill="y")
        self.text.pack(side="right", fill="both", expand=True)
        self.linenumbers.pack(side="right", fill="y")

        self.text.bind("<<Change>>", self._on_change)
        self.text.bind("<Configure>", self._on_change)

        self.console = CustomText(self)
        self.vsbConsole = tk.Scrollbar(command=self.console.yview)
        self.console.configure(yscrollcommand=self.vsbConsole.set, state=tk.DISABLED,
                               background="black", foreground="green", font=("Helvetica", "12"))
        self.console.tag_config('error', foreground="red",
                                font=("Helvetica", "12", "bold"))
        self.console.tag_config('warning', foreground="orange",
                                font=("Helvetica", "12", "bold"))
        self.console.tag_config(
            'normal', foreground="white", font=("Helvetica", "12"))
        self.console.tag_config(
            'success', foreground="green", font=("Helvetica", "12"))
        self.linenumbersConsole = TextLineNumbers(self, width=20)
        self.linenumbersConsole.attach(self.console)

        self.vsbConsole.pack(side="right", fill="y")
        self.console.pack(side="right", fill="both", expand=True)
        self.linenumbersConsole.pack(side="right", fill="y")

        self.console.bind("<<Change>>", self._on_change_console)
        self.console.bind("<Configure>", self._on_change_console)

        menu = tk.Menu(root)
        root.config(menu=menu)
        fileMenu = tk.Menu(menu)
        menu.add_cascade(label="File", menu=fileMenu)
        fileMenu.add_command(
            label="New", command=lambda: utils.newFile(self.text, self.console))
        fileMenu.add_command(
            label="Open", command=lambda: utils.openFile(root, self.text, self.console))
        fileMenu.add_command(
            label="Save", command=lambda: utils.saveFile(self.text))
        fileMenu.add_separator()
        fileMenu.add_command(label="Exit", command=utils.exitRoot)

        runMenu = tk.Menu(menu)
        menu.add_cascade(label="Compile", menu=runMenu)
        runMenu.add_command(label="Compile",
                            command=lambda: compileOnly(self, self.compiler))
        runMenu.add_command(label="Choose Compilation Directory",
                            command=lambda: utils.chooseProgDirectory(self.compiler))
        ramMenu = tk.Menu(menu)
        helpMenu = tk.Menu(menu)
        menu.add_cascade(label="Help", menu=helpMenu)
        helpMenu.add_command(label="How To Use", command=utils.showHelp)
        helpMenu.add_command(label="About", command=utils.showAbout)

        sys.stdout = utils.PrintLogger(self.console)

    def getTextArea(self):
        return self.text

    def setCompiler(self, compiler):
        self.compiler = compiler

    def getConsoleArea(self):
        return self.console

    def _on_change(self, event):
        self.linenumbers.redraw()

    def _on_change_console(self, event):
        self.linenumbersConsole.redraw()


class Compiler:
    def __init__(self):
        self.debugFile = "./Debug.txt"
        self.progFile = "./Program.asm"
        self.symbolTableFile = "./SymbolTable.txt"
        if os.name == 'nt':
            self.compilerExe = "../src/ta3myac.exe"
        else:
            self.compilerExe = "../src/ta3myac"

    def setDebugFile(self, debugFile):
        self.debugFile = debugFile

    def setProgFile(self, progFile):
        self.progFile = progFile

    def setSymbolTableFile(self, symbolTableFile):
        self.symbolTableFile = symbolTableFile

    def getDebugFile(self):
        return self.debugFile

    def getProgFile(self):
        return self.progFile

    def getSymbolTableFile(self):
        return self.symbolTableFile

    def getCompilerExe(self):
        return self.compilerExe



if __name__ == "__main__":
    root = tk.Tk()
    gui = GUI(root)
    root.title("Compiler")
    compiler = Compiler()
    gui.setCompiler(compiler)
    gui.pack(side="top", fill="both", expand=True)
    root.mainloop()
