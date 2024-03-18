Project set clock and date on led 7 segment via s32k144 microcontroller.
1. After power on, display the time: 18-00-00(date: 01.01.1991).
2. Setting date, time, alarm by LPUART serial communication.
3. Select mode display via the button.

Press button sw2
3.1. Auto display mode: Repeat display the time (5s) -> Display the date (3s).
3.2. Display the date.
3.3. Display the time.
3.4. Display the alarm. (the alarm is only set when display the alarm)

Press button sw3
Decrease bright of LED 7 SEGMENT which 5 level from maximum to off.
4. When alarm occurred, the LED Green blink with period 0.5 (s) in alarm time 10 (s). In alarm time, if pressed any button, the LED Green is OFF immediately.