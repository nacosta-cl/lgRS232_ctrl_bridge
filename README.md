# lgRS232_ctrl_bridge
Arduino replacement for a broken control panel and IR on an LG LED panel, via RS232, recieving IR signals from controller

My cat pissed so much on my tv, that the ir reciever and touch control panel stopped working. I developed a short arduino code that allows you to recieve IR signals for a TV remote control, and match it with a list of known RS232 TV commands. When it finds a match, it makes the TV perform the desired action.

Love my cat

##Hardware

Arduino, any atmega variant
TTL to rs232 adapter (MAX3232
IR reciever

##Changelog

###v1.0
*It works
###Issues
*Not that responsive, sometimes it feels stuck

