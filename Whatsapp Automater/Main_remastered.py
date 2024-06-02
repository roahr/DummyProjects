from tkinter import *
from tkinter import messagebox
from tkinter import ttk
from tkcalendar import *
import datetime as dt
from time import sleep
from os import system
import pywhatkit as messenger
import pyautogui as cur
from PIL import ImageTk, Image

io=[]
win = Tk()
win.title("WHATSAPP MESSAGE SCHEDULER")
win.geometry("1080x1710")
bg=ImageTk.PhotoImage(file = "set.png")
  
# Show image using label
label1 = Label( win, image = bg)
label1.place(x = 0, y = 0)



hour_string=StringVar()
min_string=StringVar()
sec_string=StringVar()
# last_value_sec = ""
# last_value = ""        
f = ('Arial', 24)
date=dt.datetime.now()
h_var=StringVar(win)
h_var.set(date.hour)
m_var=StringVar(win)
m_var.set(date.minute)
s_var=StringVar(win)
s_var.set(date.second)

def display_msg():
    date = cal.get_date()
    m = min_sb.get()
    h = hour_sb.get()
    s = sec_sb.get()
    t = f"Your task is set for {date} at {h}:{m}:{s}."
    msg_display.config(text=t)

    res=messagebox.askquestion(title="Confirmation", message="Do you want to continue")

    if res == "yes":
         io.append([date,h,m,s])
         win.destroy()

        
    else:
        messagebox.showinfo('Return', 'You will now return to the application screen')

       
label=Label(win,text=" CHOOSE SLOT TO SEND MESSAGE 📅 ",font="NEWTIMESROMAN 24 bold underline")
label.pack(side="top")



fone = Frame(win)
ftwo = Frame(win)

fone.pack(pady=50)
ftwo.pack(pady=30)

cal = Calendar(
    fone, 
    selectmode="day",
    year=date.year,
    month=date.month, 
    day=date.day, 
    date_patternstr="dd mm yy"
    )
cal.pack(padx=30,pady=30)

hour_sb= Spinbox(
    ftwo,
    from_=0,
    to=23,
    wrap=True,
    textvariable=h_var,
    width=2,
    state="readonly",
    font=f,
    justify=CENTER
    )
min_sb= Spinbox(
    ftwo,
    from_=0,
    to=59,
    wrap=True,
    textvariable=m_var,
    font=f,
    width=2,
    justify=CENTER
    )

sec_sb= Spinbox(
    ftwo,
    from_=0,
    to=59,
    wrap=True,
    textvariable=s_var,
    width=2,
    font=f,
    justify=CENTER
    )

hour_sb.pack(side=LEFT, fill=X, expand=True)
min_sb.pack(side=LEFT, fill=X, expand=True)
sec_sb.pack(side=LEFT, fill=X, expand=True)

msg = Label(
    win, 
    text="Hour  Minute  Seconds",
    font=("Times", 16),
    bg="#ccffff"
    )
msg.pack(side=TOP)

actionBtn =Button(
    win,
    text="Select Slot",
    font="Timesnewroman 16 bold",
    padx=10,
    pady=10,
    command=display_msg
)
actionBtn.pack(pady=30)

msg_display = Label(
    win,
    text="",
    font="Arial 22 bold",
    bg="#ccffff"
)
msg_display.pack(pady=10)

inputs=[cal.get_date(), hour_sb.get(),min_sb.get(),sec_sb.get()]


win.mainloop()



win = Tk()
win.title("WHATSAPP MESSAGE SCHEDULER")
win.geometry("1080x1710")
bg = ImageTk.PhotoImage(file = "D:\Sandbox\Sheesh\Whatsapp_scheduler\set.png")
  
# Show image using label
label1 = Label( win, image = bg)
label1.place(x = 0, y = 0)



welcome = Label(win,text=" 🤖 CHAT INFORMATIK 💬 ",font="NEWTIMESROMAN 22 bold underline")
welcome.pack(side="top")



combo = ttk.Combobox(
                state="readonly",
                height=15,
                font="NEWTIMESROMAN ",
                values=["India  +91", "Others"],
                textvariable="Country code"
            )
combo.place(x = 92, y = 122)

label=Label(win, text="Enter Phone Number With Country Code ", font=("Arial 16 bold "),bg="#ccffff")
label.pack(padx=0)

entry= Entry(win, width= 40,bd=5,font="TIMESROMAN 14 bold")
entry.focus_set()
entry.pack(pady=20)


label=Label(win, text=" Enter Message ", font=("Arial 16 bold"),bg="#ccffff")
label.pack(pady=40)

text = Text(win, height=8, width=40,font="TIMESROMAN 14 bold")
text.pack(pady=40)





def confirmation():
    cho=messagebox.askquestion(title="Confirmation", message="Do you want to continue")
    if cho == "yes":
         global entry
         global entry1
         if combo.get()=="India  +91":
            io.append("+91"+entry.get())
         else:
            io.append(entry.get())
         io.append(text.get(1.0, "end-1c"))
         win.destroy()

    else:
        messagebox.showinfo('Return', 'You will now return to the application screen')


switch=Button(win,text="SUBMIT",font="Timesnewroman 20 bold",command=confirmation)
switch.pack(pady=20)

win.mainloop()







def start_approval(schedule):
    sch_date=schedule[0][0].split("/")
    h,m=schedule[0][1],schedule[0][2]


    while True:
        local_date=dt.date.today()
        local_time=dt.datetime.now()
        local_date=dt.date.today()
        dt1 = dt.datetime.now() 
        dt2 = dt.datetime(int("20"+sch_date[2]),int(sch_date[0]),int(sch_date[1]),int(h),int(m))
        tdelta = dt2 - dt1 
        cond=tdelta.total_seconds()

        if str(local_date.year)=="20"+sch_date[2] and str(local_date.month)==sch_date[0] and str(local_date.day)==sch_date[1] and str(local_time.hour)==h and str(local_time.minute)==m :
                print("====================================================================================")
                print("Task sequence initialized ✅")
                return True
            

        elif  cond<0:
             messagebox.showinfo('WARNING⚠️', "❌Enter Valid Time Slot❌\nError : Can't send message to past",icon="warning")
             exit()
            


        else:
            system('clear')
            print("====================================================================================")
            print("-*-*-*-*-*-*-*-*-*-*-*-*-𝕎𝕙𝕒𝕥𝕤𝕒𝕡𝕡 𝕄𝕖𝕤𝕤𝕒𝕘𝕖 𝕊𝕔𝕙𝕖𝕕𝕦𝕝𝕖𝕣*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-")
            print("====================================================================================")
            print("\n\tLocal Date & Time     : ",dt.datetime.now().year," - ",dt.datetime.now().month," - ",dt.datetime.now().day,"  ",dt.datetime.now().hour," : ",dt.datetime.now().minute," : ",dt.datetime.now().second)
            print("\n\tPhone Number          : ",schedule[1])
            print("\n\tMessage               : ",schedule[2])
            print("\n\tScheduled Date & Time : ","20",sch_date[2]," - ",sch_date[0]," - ",sch_date[1],"  ",h," : ",m," : 00")
            print("\n\tTime To Trigger action : ",tdelta)
            sleep(0.9)

if start_approval(io)==True:
        messenger.sendwhatmsg_instantly(io[1],io[2])
        n=dt.datetime.now()
        name=n.strftime("%Y_%m_%d_%H_%M_%S")

        root=r'D:\Sheesh\Whatsapp_scheduler\whatsapp_project_data\{}.jpg'.format(name)

        cur.press("enter")
        sleep(3.5)

        myScreenshot = cur.screenshot()
        myScreenshot.save(root)

        sleep(0.1)

        with cur.hold("ctrl"):
            cur.press("w")

        sleep(0.3)

        print("====================================================================================")
        print("Message Sent....✅")
        print("====================================================================================")
        
        win= Tk()
        win.title("WHATSAPP MESSAGE SCHEDULER")
        win.geometry("1920x1080")
        win.config(bg="#e6ccff")
        bg = ImageTk.PhotoImage(file = "D:\Sandbox\Sheesh\Whatsapp_scheduler\set.png")
  
        # Show image using label
        label1 = Label( win, image = bg)
        label1.place(x = 0, y = 0)


        frame = Frame(win, width=400, height=225)
        frame.pack()
        frame.place(anchor='center', relx=0.5, rely=0.5)

        # Create an object of tkinter ImageTk
        img = ImageTk.PhotoImage(Image.open(root))

        # Create a Label Widget to display the text or Image
        label = Label(frame, image = img)
        label.pack()

   
        messagebox.showinfo('Successfull', 'Press enter to exit',icon="warning")
        win.destroy()
        win.mainloop()       
        exit()



"""
Need to work
# * Set default start time 
# * Make the window dynamically resize and scale
# * Format task string within the windowfwwfffffff
# * Fix strings on top
#* Show message in tkinter window if the task failes
* If possible, a dropdown menu for country code
#* Bigger message box which allows newlines as well, Parse newlines and send accordingly
# * If possible, show the countdown message in tkinter window
    # - Few ways of approaching this would be 
    # 1. Create a terminal window inside the tkinter window
    # 2. Close the tkinter window and then force open 
"""