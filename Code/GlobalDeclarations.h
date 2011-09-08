
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

// Board Configuration byte
__no_init uint8_t BOARDCONFIG @ 0x08007800;

// Midi Channel configurations
// Midi mode, sets the mode that the current pin is in. Ignored in matrix switch mode
__no_init uint8_t MIDI0MODE @ 0x08007801;
__no_init uint8_t MIDI1MODE @ 0x08007802;
__no_init uint8_t MIDI2MODE @ 0x08007803;
__no_init uint8_t MIDI3MODE @ 0x08007804;
__no_init uint8_t MIDI4MODE @ 0x08007805;
__no_init uint8_t MIDI5MODE @ 0x08007806;
__no_init uint8_t MIDI6MODE @ 0x08007807;
__no_init uint8_t MIDI7MODE @ 0x08007808;
__no_init uint8_t MIDI8MODE @ 0x08007809;
__no_init uint8_t MIDI9MODE @ 0x0800780a;
__no_init uint8_t MIDI10MODE @ 0x0800780b;
__no_init uint8_t MIDI11MODE @ 0x0800780c;
__no_init uint8_t MIDI12MODE @ 0x0800780d;
__no_init uint8_t MIDI13MODE @ 0x0800780e;



__no_init uint8_t MIDI0POL @ 0x0800780f;
__no_init uint8_t MIDI1POL @ 0x08007810;
__no_init uint8_t MIDI2POL @ 0x08007811;
__no_init uint8_t MIDI3POL @ 0x08007812;
__no_init uint8_t MIDI4POL @ 0x08007813;
__no_init uint8_t MIDI5POL @ 0x08007814;
__no_init uint8_t MIDI6POL @ 0x08007815;
__no_init uint8_t MIDI7POL @ 0x08007816;
__no_init uint8_t MIDI8POL @ 0x08007817;
__no_init uint8_t MIDI9POL @ 0x08007818;
__no_init uint8_t MIDI10POL @ 0x08007819;
__no_init uint8_t MIDI11POL @ 0x0800781a;
__no_init uint8_t MIDI12POL @ 0x0800781b;
__no_init uint8_t MIDI13POL @ 0x0800781c;



__no_init uint8_t MIDI0SENS @ 0x0800781d;
__no_init uint8_t MIDI1SENS @ 0x0800781e;
__no_init uint8_t MIDI2SENS @ 0x0800781f;
__no_init uint8_t MIDI3SENS @ 0x08007820;
__no_init uint8_t MIDI4SENS @ 0x08007821;
__no_init uint8_t MIDI5SENS @ 0x08007822;
__no_init uint8_t MIDI6SENS @ 0x08007823;
__no_init uint8_t MIDI7SENS @ 0x08007824;
__no_init uint8_t MIDI8SENS @ 0x08007825;
__no_init uint8_t MIDI9SENS @ 0x08007826;
__no_init uint8_t MIDI10SENS @ 0x0800787;
__no_init uint8_t MIDI11SENS @ 0x08007828;
__no_init uint8_t MIDI12SENS @ 0x08007829;
__no_init uint8_t MIDI13SENS @ 0x0800782a;
__no_init uint8_t MIDI14SENS @ 0x0800782b;



__no_init uint8_t MIDI0CURVE @ 0x0800782c;
__no_init uint8_t MIDI1CURVE @ 0x0800782d;
__no_init uint8_t MIDI2CURVE @ 0x0800782e;
__no_init uint8_t MIDI3CURVE @ 0x0800782f;
__no_init uint8_t MIDI4CURVE @ 0x08007830;
__no_init uint8_t MIDI5CURVE @ 0x08007831;
__no_init uint8_t MIDI6CURVE @ 0x08007832;
__no_init uint8_t MIDI7CURVE @ 0x08007833;
__no_init uint8_t MIDI8CURVE @ 0x08007834;
__no_init uint8_t MIDI9CURVE @ 0x08007835;
__no_init uint8_t MIDI10CURVE @ 0x08007836;
__no_init uint8_t MIDI11CURVE @ 0x08007837;
__no_init uint8_t MIDI12CURVE @ 0x08007838;
__no_init uint8_t MIDI13CURVE @ 0x08007839;



__no_init uint8_t MIDI0OFFSET @ 0x0800783a;
__no_init uint8_t MIDI1OFFSET @ 0x0800783b;
__no_init uint8_t MIDI2OFFSET @ 0x0800783c;
__no_init uint8_t MIDI3OFFSET @ 0x0800783d;
__no_init uint8_t MIDI4OFFSET @ 0x0800783e;
__no_init uint8_t MIDI5OFFSET @ 0x0800783f;
__no_init uint8_t MIDI6OFFSET @ 0x08007840;
__no_init uint8_t MIDI7OFFSET @ 0x08007841;
__no_init uint8_t MIDI8OFFSET @ 0x08007842;
__no_init uint8_t MIDI9OFFSET @ 0x08007843;
__no_init uint8_t MIDI10OFFSET @ 0x08007844;
__no_init uint8_t MIDI11OFFSET @ 0x08007845;
__no_init uint8_t MIDI12OFFSET @ 0x08007846;
__no_init uint8_t MIDI13OFFSET @ 0x08007847;



__no_init uint8_t MIDI0NOTE@ 0x08007848;
__no_init uint8_t MIDI1NOTE@ 0x08007849;
__no_init uint8_t MIDI2NOTE@ 0x0800784a;
__no_init uint8_t MIDI3NOTE@ 0x0800784b;
__no_init uint8_t MIDI4NOTE@ 0x0800784c;
__no_init uint8_t MIDI5NOTE@ 0x0800784d;
__no_init uint8_t MIDI6NOTE@ 0x0800784e;
__no_init uint8_t MIDI7NOTE@ 0x0800784f;
__no_init uint8_t MIDI8NOTE@ 0x08007850;
__no_init uint8_t MIDI9NOTE@ 0x08007850;
__no_init uint8_t MIDI10NOTE@ 0x08007850;
__no_init uint8_t MIDI11NOTE@ 0x08007850;
__no_init uint8_t MIDI12NOTE@ 0x08007850;
__no_init uint8_t MIDI13NOTE@ 0x08007850;