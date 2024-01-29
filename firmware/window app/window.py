import tkinter as tk
from tkinter import ttk
import serial # Do obsługi portu COM

def connect_to_com_port():
    selected_com_port = com_port_var.get()
    baud_rate = 115200  # Domyślna szybkość transmisji (możesz dostosować do własnych potrzeb)

    try:
        serial_ = serial.Serial(selected_com_port, baud_rate, timeout=0, parity=serial.PARITY_EVEN, rtscts=1)
        print(f"Connected to {selected_com_port}")
        # Tutaj możesz dodać kod obsługi połączenia
    except:
        print(f"Error")

def set_speed(val):
    str_val = str(int(float(val)))
    command = ''
    if len(str_val) == 3:
        command = 's0' + str_val
    else:
        command = 's' + str_val
    selected_com_port = com_port_var.get()
    baud_rate = 115200  # Domyślna szybkość transmisji (możesz dostosować do własnych potrzeb)
    try:
        ser = serial.Serial(selected_com_port, baud_rate, timeout=0, parity=serial.PARITY_EVEN, rtscts=1)
        ser.write(command.encode(encoding = 'ascii', errors = 'strict'))
        # Tutaj możesz dodać kod obsługi połączenia
    except:
        print(f"Error")
    

def read_from_com_port(ser):
    data = ser.readline().decode("utf-8")
    ser.cle
    if data:
        text_box.insert(tk.END, data)
        text_box.see(tk.END)  # Przewiń do najnowszej linii
    root.after(100, read_from_com_port, ser)  # Ponowne uruchomienie funkcji po 100 ms

# Utwórz główne okno
root = tk.Tk()
root.title("COM Port Connection")

# Utwórz etykietę, rozwijalną listę i przypisz dostępne porty COM
com_label = ttk.Label(root, text="Choose COM Port:")
com_label.grid(row=0, column=0, padx=10, pady=10, sticky=tk.W)

available_com_ports = [f"COM{i}" for i in range(1, 10)]
com_port_var = tk.StringVar(value=available_com_ports[0])

com_dropdown = ttk.Combobox(root, textvariable=com_port_var, values=available_com_ports)
com_dropdown.grid(row=0, column=1, padx=10, pady=10, sticky=tk.W)

# Utwórz suwak
slider_label = ttk.Label(root, text="Slider:")
slider_label.grid(row=1, column=0, padx=10, pady=10, sticky=tk.W)

slider_var = tk.DoubleVar(value=0)
slider = ttk.Scale(root, variable=slider_var, from_=500, to=3500, orient=tk.HORIZONTAL, command=set_speed)
slider.grid(row=1, column=1, padx=10, pady=10, sticky=tk.W)

# Utwórz przycisk do nawiązywania połączenia
connect_button = ttk.Button(root, text="Connect", command=connect_to_com_port)
connect_button.grid(row=2, column=0, columnspan=2, pady=20)

text_box = tk.Text(root, height=10, width=50)
text_box.grid(row=3, column=0, columnspan=2, padx=10, pady=10)

# Uruchom pętlę zdarzeń
root.mainloop()
