
//----------------------- Global Declarations -------------------------------





// ************************ Global Functions ********************************

extern u8 DefaultConfiguration(void);
extern u8 Configure_UART();
extern u8 UART_Send(u8 DataToSend);
extern u8 ReadKeyboard();
extern u8 SendMessage();

// Midi Commands

// Channel Voice Message
extern u8 Midi_Note_Off(u8 _u8_channel, u8 _u8_note, u8 _u8_velocity);
extern u8 Midi_Note_On(u8 _u8_channel, u8 _u8_note, u8 _u8_velocity);
extern u8 Midi_Poly_Key_Pressure(u8 _u8_channel, u8 _u8_note, u8 _u8_velocity);
extern u8 Midi_Control_Change(u8 _u8_channel, u8 _u8_controller, u8 _u8_value);
extern u8 Midi_Program_Change(u8 _u8_channel, u8 _u8_program);
extern u8 Midi_Channel_Pressure(u8 _u8_channel, u8 _u8_pressure);
extern u8 Midi_Pitch_Wheel(u8 _u8_channel, u16 _u16_value);

// Channel Mode Messages
extern u8 Midi_Sound_Off(u8 _u8_channel);
extern u8 Midi_Reset_All_Controllers(u8 _u8_channel);
extern u8 Midi_Local_Control(u8 _u8_channel);
extern u8 Midi_All_Notes_Off(u8 _u8_channel);




// ************************ Static Flash Variables ********************************

// These are variables that are stored in flash so that configurations are retained after powering down
// 0x0800 7800 to 0800 7FFF are being used for these variables. This is the top 2kb of the 32kb version of the uC

// Midi Channel Modes


// Midi mode, sets the mode that the current pin is in. Ignored in matrix switch mode
__no_init uint32_t MIDI0MODE @ 0x08007800;
//#pragma required=MIDI0MODE
