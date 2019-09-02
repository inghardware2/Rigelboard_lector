
#include <FastCRC.h>
FastCRC16 CRC16;
// the setup function runs once when you press reset or power the board
#define P_bzz 9
#define f_tono_ok      2200
  #define f_tono_fail    500
#define t_tono_ok      50
#define t_tono_fail    250
#define TimeOut         8      //Tiempo de espera para captura de huella

int32_t _SN                   =0;

bool ctj                      =false;
int  Trigger_Delay           =             1,        // (msec) Delay btw Pres. Detect and Acq
  _TimeOut                   =             0,          // (sec) Timeout on Blocking Ops
  Override_Trigger           =             1,     // if TRUE, override presence detection
  Override_HeartBeat_Display =             0, // if TRUE, Turns off HeartBeat
  Override_Default_LED       =             1,   // if TRUE, Turns off default LED behavior
  Match_Threshold            =             0,      // Thresold Score for Matching
  Set_Exposure_Mode          =             1,      // Manual or Auto Exposure Mode   
  Select_PreProc             =             0,       // Bitfield to Select PreProcessor
  Select_Identifier          =             1,      // Bitfield to Select Identifier
  Select_Matcher             =             0,       // Bitfield to Select Matcher
  Select_Extractor           =             1,    // Bitfield to Select Extractor
  Select_Spoof_Model         =             0,     // Bitfield to Select Spoof Model   1: no devuelve Score -- 0:devuelve Score
  Select_Template_Format     =             0;   // Template Format    1 template ANSI -- 0:Template ISO    

  
//int pin =2;
int inRecepcion=0;
int lector_listo=0;

bool act=false;
//int i=0;
int PROXIMO_ENVIO=1;
int No_cmd=0;
int16_t Sz_template=0;              
bool activar_todo             =false;
bool activar_rx               =false;
bool envio_67                 =false;
bool envio_EOT                =false;

bool EOT_rx                   =false;
bool solicitar_template       =false;
bool enviar_comando_template  =false;
bool activar_rx_template      =false;
bool captura_end              = false;
bool Xmodem                   =false;
bool rx_star_mcu              =false;
bool setup_dev                =false;
//  sección  Match ********** //
bool act_Match                =false;
bool capture                  =false;
int cnt_captura               =0;
bool act_next_temp_Match      =false;
bool end_match                =false;
bool nextt                    =false;

bool Enroll                  =false;
int insert                   =0;
bool sensor_enable           =true;
bool matcher                 =false;
bool Multi_matchers          =0;
int cnt_matcher              =0;
bool send_tmp                =false;
int cnt_result               =0;
bool send_tmp_enr            =false;

int32_t Threshold            =25000;

int32_t score_match          =0;
int32_t ScoreMatch1          =0;
int32_t ScoreMatch2          =0;
int32_t ScoreMatch3          =0;
bool result                  =false;
//byte Tmp_rx[SzTmps]                  ;
//byte Tmp_rx[1300]                   ;
//byte Template [SzTmps];
bool setupd                 =true;
bool validacion                  =false;
bool act_Terminal           =true;

bool match2                 =false;
bool match3                 =false;
int insert2                 =0;
int16_t g                   =0;
//byte tmp2[]={0x23, 0x03, 0x00, 0x00, 0x46, 0x4D, 0x52, 0x00, 0x20, 0x32, 0x30, 0x00, 0x03, 0x23, 0x00, 0x35, 0x00, 0x17, 0x00, 0x00, 0x01, 0x18, 0x01, 0x60, 0x00, 0xC5, 0x00, 0xC5, 0x01, 0x00, 0x00, 0x00, 0x00, 0x24, 0x80, 0x56, 0x00, 0x17, 0x63, 0x0F, 0x40, 0xE7, 0x00, 0x23, 0x51, 0x0F, 0x40, 0xF6, 0x00, 0x44, 0x9F, 0x0E, 0x40, 0x83, 0x00, 0x46, 0x04, 0x0F, 0x40, 0x3B, 0x00, 0x49, 0x0C, 0x0F, 0x40, 0xA2, 0x00, 0x51, 0x5F, 0x0F, 0x80, 0x7C, 0x00, 0x59, 0x68, 0x0F, 0x80, 0x94, 0x00, 0x5E, 0x00, 0x0F, 0x40, 0x22, 0x00, 0x6C, 0x75, 0x0F, 0x40, 0x5A, 0x00, 0x86, 0x75, 0x0F, 0x40, 0xB5, 0x00, 0x87, 0x5B, 0x0F, 0x40, 0xCE, 0x00, 0x87, 0x47, 0x0F, 0x40, 0xF0, 0x00, 0x96, 0x8F, 0x0F, 0x40, 0xA0, 0x00, 0x97, 0xAC, 0x0F, 0x40, 0x7F, 0x00, 0xA2, 0x78, 0x0F, 0x40, 0x82, 0x00, 0xBD, 0x83, 0x0F, 0x40, 0x24, 0x00, 0xBF, 0x79, 0x0F, 0x80, 0xA9, 0x00, 0xC1, 0x7E, 0x0D, 0x40, 0x34, 0x00, 0xD7, 0x80, 0x0F, 0x40, 0x90, 0x00, 0xD5, 0x25, 0x0E, 0x40, 0x62, 0x00, 0xE7, 0x8A, 0x0F, 0x40, 0xE9, 0x00, 0xEA, 0x80, 0x0F, 0x40, 0xC6, 0x00, 0xEE, 0x74, 0x0F, 0x40, 0x90, 0x00, 0xFF, 0xB3, 0x0D, 0x40, 0xD5, 0x01, 0x03, 0x77, 0x0F, 0x40, 0xA9, 0x01, 0x06, 0x59, 0x0F, 0x40, 0xF6, 0x01, 0x0B, 0x81, 0x0F, 0x80, 0x68, 0x01, 0x0E, 0x96, 0x0F, 0x80, 0xB6, 0x01, 0x13, 0x6A, 0x0F, 0x80, 0x45, 0x01, 0x21, 0x8F, 0x04, 0x80, 0xD8, 0x01, 0x23, 0x76, 0x0F, 0x40, 0x87, 0x01, 0x27, 0x01, 0x0C, 0x40, 0x5C, 0x01, 0x2D, 0xA0, 0x08, 0x40, 0x45, 0x01, 0x32, 0x33, 0x01, 0x80, 0x3F, 0x01, 0x33, 0x9C, 0x01, 0x80, 0x91, 0x01, 0x37, 0x4E, 0x0F, 0x02, 0x2B, 0x01, 0x01, 0x02, 0x2B, 0x49, 0x43, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x35, 0x01, 0x02, 0x0D, 0x19, 0xF3, 0x03, 0x00, 0xE1, 0x12, 0x13, 0xC0, 0x03, 0x00, 0xC4, 0x13, 0x06, 0xFE, 0x08, 0x00, 0x84, 0x13, 0x7D, 0xC2, 0xC0, 0xC3, 0x51, 0x04, 0x00, 0x53, 0x18, 0x70, 0x59, 0x11, 0x00, 0xE6, 0x25, 0x8C, 0xC0, 0xC3, 0xFE, 0xC2, 0x5C, 0xC1, 0x7B, 0x7C, 0xC0, 0x0F, 0x00, 0xF0, 0x41, 0x97, 0x8B, 0xC2, 0x5C, 0x77, 0x5A, 0x0C, 0x00, 0x86, 0x43, 0xFA, 0x3D, 0x35, 0x33, 0xC0, 0x11, 0x00, 0x3C, 0x45, 0xE7, 0xFE, 0x4A, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0x30, 0xC2, 0xFB, 0xC3, 0x0B, 0x00, 0x7E, 0x48, 0x77, 0xC3, 0x45, 0x88, 0x5C, 0x0C, 0x00, 0x86, 0x49, 0xFD, 0x3D, 0xFE, 0x3D, 0xFD, 0x52, 0x04, 0x00, 0x36, 0x4C, 0x62, 0xC0, 0xC0, 0x0A, 0x00, 0xA8, 0x51, 0x09, 0xFF, 0xFF, 0xFF, 0x31, 0x47, 0x0D, 0x00, 0xA0, 0x55, 0x77, 0x8B, 0xC0, 0xC1, 0x71, 0x70, 0x0C, 0x00, 0x7A, 0x5B, 0x6D, 0xC0, 0xC2, 0x66, 0xC3, 0x51, 0xFE, 0x09, 0x00, 0x98, 0x5D, 0xFD, 0x29, 0x2A, 0xC0, 0x14, 0x00, 0x28, 0x67, 0xE7, 0xC1, 0xFD, 0x58, 0xC0, 0x3E, 0x40, 0xFF, 0x33, 0x47, 0x1B, 0x00, 0x5F, 0x83, 0xE4, 0x4B, 0xFD, 0xFF, 0xFE, 0xFF, 0xFD, 0xFE, 0xFE, 0xFF, 0xFE, 0xC0, 0xFF, 0xC0, 0xFE, 0xFF, 0xC1, 0xC0, 0xFD, 0xC1, 0xFD, 0xC1, 0xFF, 0xC0, 0x11, 0x00, 0xB3, 0x84, 0x89, 0xC3, 0xC4, 0xC2, 0xC0, 0x8C, 0x7B, 0xC3, 0xFE, 0x87, 0x0F, 0x00, 0x57, 0x86, 0x60, 0x7F, 0x72, 0xC0, 0xFF, 0xC2, 0xC1, 0xC0, 0xC2, 0xC3, 0x18, 0x00, 0xD0, 0x86, 0xA2, 0xC2, 0xC2, 0xC3, 0x9B, 0xC1, 0x86, 0x62, 0xC0, 0xC3, 0x59, 0x72, 0xC3, 0x07, 0x00, 0x5C, 0x8A, 0x56, 0x56, 0x6A, 0x11, 0x00, 0xBB, 0x8A, 0x1A, 0x2A, 0x2E, 0x4F, 0xFF, 0xFF, 0x3C, 0xFC, 0x18, 0x00, 0xCB, 0x8A, 0x9C, 0x9B, 0xC2, 0xC4, 0xC0, 0x8B, 0xC2, 0x6A, 0xC2, 0xFF, 0x77, 0xC2, 0x86, 0x05, 0x00, 0xB4, 0x8B, 0x83, 0x9F, 0x0A, 0x00, 0xD2, 0x8E, 0x2B, 0x38, 0x2B, 0x3F, 0x09, 0x00, 0xA3, 0x94, 0x00, 0xFE, 0xF9, 0xFE, 0xFE, 0xFE, 0x31, 0x05, 0x00, 0xF3, 0x96, 0x2D, 0xFE, 0x51, 0x09, 0x00, 0xED, 0x98, 0x34, 0xC0, 0xFD, 0xC1, 0xFF, 0xC0, 0x5B, 0x03, 0x00, 0x9B, 0x9A, 0x67, 0xC4, 0x0C, 0x00, 0xA3, 0x9B, 0x09, 0xFC, 0xFC, 0xFC, 0xC0, 0xFC, 0xFF, 0xFD, 0xFD, 0xFD, 0xFF, 0x06, 0x00, 0x7C, 0xA1, 0x5E, 0xC3, 0x6F, 0x11, 0x00, 0x82, 0xA5, 0x57, 0x77, 0xC3, 0x80, 0xC0, 0xC4, 0xC7, 0xC4, 0xC2, 0xC1, 0xC2, 0xC2, 0x0F, 0x00, 0x0F, 0xB7, 0xD6, 0x58, 0xC0, 0xFE, 0xFF, 0xC0, 0xFE, 0x4B, 0x44, 0x07, 0x00, 0x7F, 0xBE, 0x50, 0xA0, 0x71, 0x05, 0x00, 0x85, 0xBE, 0x46, 0x90, 0x0C, 0x00, 0xA7, 0xBE, 0x62, 0xC6, 0xC2, 0xCF, 0xCD, 0xC1, 0xC4, 0xC6, 0xCE, 0xC6, 0xC3, 0x03, 0x00, 0x21, 0xBF, 0x5E, 0xC4, 0x05, 0x00, 0x26, 0xC2, 0x50, 0xFF, 0x7B, 0x04, 0x00, 0xFF, 0xD0, 0x40, 0x6C, 0x09, 0x00, 0x31, 0xD8, 0x4F, 0xC1, 0xC0, 0x79, 0x83, 0x09, 0x00, 0x38, 0xDA, 0x46, 0xFF, 0x6F, 0xC2, 0x82, 0x09, 0x00, 0x5F, 0xEA, 0x43, 0x70, 0xC5, 0xC2, 0x96, 0x06, 0x00, 0x66, 0xEA, 0x3A, 0xC1, 0x89, 0x08, 0x00, 0xE7, 0xEC, 0x49, 0xC0, 0xFF, 0xFE, 0x3F, 0x07, 0x10, 0xD3, 0x04, 0x5A, 0xC0, 0xC0, 0x2E, 0x07, 0x10, 0xD9, 0x06, 0x53, 0xFF, 0x3E, 0xFD, 0x05, 0x10, 0xF2, 0x0D, 0x49, 0xFE, 0x60, 0x05, 0x10, 0xF9, 0x0D, 0x40, 0xFE, 0xFC, 0xC1, 0x05, 0x10, 0x6A, 0x13, 0x30, 0xC3, 0xC3, 0xC2, 0x04, 0x10, 0xB5, 0x15, 0x67, 0xFF, 0xFD, 0x03, 0x10, 0xD6, 0x27, 0x57, 0xC0, 0x03, 0x10, 0x5A, 0x2F, 0x24, 0xC2, 0x03, 0x10, 0x7B, 0x40, 0x96, 0xC0};

//byte Template2[1300];
/////******** fin variables match*********//
int torniquete = 3;


int8_t p_Lector =A8;

bool access =false;
int LED_val=PB6;
int delay_tq=50;

int cnt_sol_envio=0;
//int TimeOut=10; // en segundos
int cnt_timeout=0;
int cnt_tmp=0;

byte arg[]={0, 0};
byte __opaquedate[]={};

      char inChar;
      String mcu_Peticion="";
long Spoof =5050;
int32_t timer=0;
int a=0;
int Z=0;

bool ACT=false;


void setup() {
  
Serial1.begin(57600);   // A2 TX- A3    RX //comunicacion con el lector
Serial2.begin(57600);   //Comunicacion con el PC  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(torniquete, OUTPUT);
  pinMode(LED_val, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  delay(1000);
  digitalWrite(5, HIGH);

  pinMode(A8, OUTPUT); //Reinicio Electrico
  digitalWrite(A8, HIGH);

  Threshold = 30000;
  //getSerial();
  Serial2.println("M3BLOR Online");
  ///mcu_Peticion="configurar";
  //wdt_enable(WDTO_8S);
}
void serialEvent2()
{

  while (Serial2.available()&&(ctj==false)) {
    // get the new byte:
    
    // get the new byte:
    int value=0;
    char inChar = (char)Serial2.read();
    value=int(inChar);
    //Serial1.print(',');
    //Serial1.write(inChar);
    // add it to the inputString:

    if((value!=10))
    //if((inChar!='\n'))
    {mcu_Peticion += inChar; }

    if ((value ==10))
    //if((inChar!='\n'))
    {
   //   stringComplete = true;
   
      mcu_rx(true);

    }

  }  
  }
   void serialEvent1()
  {
     // inRecepcion=0;
      lector_listo=0;
      //mcu_Peticion="";
        if (Serial1.available()>0)
          {
            lector_listo=0;
            lector_listo = Serial1.read();  
            //Serial2.write(lector_listo);
            if((lector_listo==4)&&(captura_end==false))
            {
              EOT_rx=true;
             
              }
          }

                    ////// MATCH ////////////////////////////
                    
              if((match2==true))
              {

              matcher=true;
                Matcher_match();
                insert2=0;
                }


if(inRecepcion==105)      
{

  match2=true;  
  insert2 =1;
  
  //captura();
  //captura();
      
  }

                      //////////// ENROLAMIENTO  ////////////////////////                  
              if (matcher==true)
              {
              Matcher_Enroll();
              }
            if(result==true)
            {
              //select_tmp();
              result=false;
              }




              ////////////////////////////////////
                                     
     if ((solicitar_template==true))
    {
     //lector_listo=0;
      if (enviar_comando_template==false)
      {
        envio(true,0x15,1);            
        enviar_comando_template=true;
      }
        else
          {
             PROXIMO_ENVIO=8;
             activar_todo=true;
             solicitar_template=false;
             
          }
      }             
    if((EOT_rx==true))
   {
      if(PROXIMO_ENVIO >3)
      {
      PROXIMO_ENVIO ++;
        activar_todo=true;
        
        if(PROXIMO_ENVIO ==4)
        {
          //delay(1000);
        }
        


            envio(true,21,1);       
          
        lector_listo=0;
        inRecepcion=0;
        EOT_rx=false;
        Spoof==5050;
        //solicitar_template=false;   
      }
    
    
    }
    if((setup_dev==true)||(EOT_rx==true))
    {
        
        
        if((PROXIMO_ENVIO>0)&&(PROXIMO_ENVIO<3))
        {PROXIMO_ENVIO ++;
        activar_todo=true;
        
        if(PROXIMO_ENVIO ==4)
        {
         // delay(1000);
        }
           envio(true,21,1);                 
        }
        
        lector_listo=0;
        inRecepcion=0;
        EOT_rx=false;
        Spoof==5050;
        //solicitar_template=false;   
        setup_dev=false;
    }
    if (activar_todo==true)
    {
      
          inicio(PROXIMO_ENVIO);
          preparar_rx();            
        
       // activar_todo=false;
      }
         if(activar_rx==true)
      {
          finalizar();
          
        }
       

      }  

    void mcu_rx(bool rx)
    {
      bool act_rx;
      act_rx = rx;
      while(act_rx==true)
      {
     if((mcu_Peticion.length()>0))
      {
        Serial2.println(mcu_Peticion);
        if((mcu_Peticion!="xmodem")&&(mcu_Peticion!="noxmodem")&&(mcu_Peticion!="serial")&&(mcu_Peticion!="captura")&&(mcu_Peticion!="revfirmware")&&(mcu_Peticion!="configurar")&&(mcu_Peticion!="iso")&&(mcu_Peticion!="ansi")&&(mcu_Peticion!="match")&&(mcu_Peticion!="enroll")&&(mcu_Peticion!="tenroll")&&(mcu_Peticion!="reset")&&(mcu_Peticion!="start")&&(mcu_Peticion!="match2")&&(mcu_Peticion!="reset_ad")&&(mcu_Peticion!="read")&&(mcu_Peticion!="read2")&&(mcu_Peticion!="read3")&&(mcu_Peticion!="activar_tq")&&(mcu_Peticion!="ready")&&(mcu_Peticion!="reporte")&&(mcu_Peticion!="limpiarReg")&&(mcu_Peticion!="reset_lector")&&(mcu_Peticion!="resetBTI")&&(mcu_Peticion!="requestBTI")&&(mcu_Peticion!="linkBTI")&&(mcu_Peticion!="onBTI")&&(mcu_Peticion!="offBTI"))
      {
        //Serial2.println("error");
        Serial2.flush();mcu_Peticion="";
      }
      else{
        /*Serial1.print("aceptado");*/
        }
       }        
      
      if(mcu_Peticion=="xmodem")
      {Xmodem=true;mcu_Peticion="";}

      if(mcu_Peticion=="limpiarReg")
      {Xmodem=true;mcu_Peticion="";//limpiarReg();
      }      
      if(mcu_Peticion=="reporte")
      {mcu_Peticion="";
      //reporte();
      }      
      if(mcu_Peticion=="ready")
      {Xmodem=true;mcu_Peticion="";delay(2000);Serial2.println("Listo");}
      else if(mcu_Peticion=="noxmodem")
      {Xmodem=false;mcu_Peticion="";}
      else if(mcu_Peticion=="configurar")
      {mcu_Peticion="";//setUpLector();
      }      
      else if(mcu_Peticion=="match")
      {mcu_Peticion="";
      /*digitalWrite(torniquete,LOW);
      delay(50);
      digitalWrite(torniquete,HIGH);*/
      if(ACT==false)
      {
        ACT=true;
      captura();
      }

      }  
      else if(mcu_Peticion=="serial")
      {mcu_Peticion="";//getSerial();
      inRecepcion=85;
      //Serial2.println("serial ");
      }  
      else if(mcu_Peticion=="revfirmware")
      {mcu_Peticion="";inRecepcion=86;}      
      else if(mcu_Peticion=="iso")
      {mcu_Peticion="";//Select_Template_Format=0;
      inRecepcion=87;}
      else if(mcu_Peticion=="ansi")
      {mcu_Peticion="";//Select_Template_Format=1;
      inRecepcion=87;
      }
      
     

      else if(mcu_Peticion=="reset")
      {mcu_Peticion="";reset_lector();
      }      
              
      else if(mcu_Peticion=="activar_tq")
      {mcu_Peticion="";activar_tq();
      }      

      else if(mcu_Peticion=="linkBTI")
      {
        mcu_Peticion="";
     //   CheckLinkBTI();
      }
      else if(mcu_Peticion=="resetBTI")
      {
        mcu_Peticion="";
       // ResetBTI();       
      }
      else if(mcu_Peticion=="requestBTI")
      {          
        mcu_Peticion="";        
       // RequestBTI(0);
      }
      else if(mcu_Peticion=="onBTI")
      {
        mcu_Peticion="";
      //  switchBTI(true);  
     //  ActiveBTI(true);     
      }                   
      else if(mcu_Peticion=="offBTI")
      {
        mcu_Peticion="";
       // ActiveBTI(false);   
       // switchBTI(false);
      }                                          
      

          act_rx=false;
      }
      }  
      void reset_lector()
      {
        /*digitalWrite(p_Lector, LOW);
        delay(2000);
        digitalWrite(p_Lector, HIGH);*/
        digitalWrite(p_Lector, LOW);
        delay(3000);
        digitalWrite(p_Lector, HIGH);
        digitalWrite(torniquete,HIGH);// inicia en alto porque va conectado a un timmer 556 cuyo trigger es con flancos de bajadas
        }
      void activar_tq()
      {
        
            //  Serial1.println("Match Successfull Successfull Successfull Successfull Successfull");
              Serial2.println("ID Successful");              
              digitalWrite(torniquete, LOW);
   
              delay(delay_tq);
              digitalWrite(torniquete, HIGH);            
              delay(500);

              //digitalWrite(LED_val, LOW);
              ACT =false;
              //contadorFP();
              access=false;
              //reset();
              //contadorCD();
             // contador();
              
        }
               void Matcher_match()
        {
         if (matcher==true)
         {
              preparar_rx();
          //    Serial2.println("oki");      //DEBUG

             if(lector_listo==0x15)
              {
                preparar_rx();
              matcher=false;       

                }                  
          }
          
          }
        void Matcher_Enroll()
        {
         if (matcher==true)
         {
              preparar_rx();
          //    Serial2.println("oki");      //DEBUG
            inRecepcion=0;
             if(lector_listo==0x15)
              {
                preparar_rx();
              matcher=false;       
              Multi_matchers=true;    
              inRecepcion=0;
       
                }                  
          }
         
        }
                    void envio(bool act,int valor, int repeticiones)
  {
    while(act==true)
    {
    for(int i=0; i<=repeticiones; i++)
      {
        Serial1.write(valor);
      }
      act=false;
    }
    }

void generar_cmd_vector(int cmdx, byte arg[1],byte opaquedate[],int16_t LenOpaqueDate )
{  
  byte cmd_t[133];
uint8_t datos[128];
  int _size_vector_cmd=128;
  int No_zeros=0;
  int posicion_CtlZ=0;
  int _szopaquedate= 0;
  _szopaquedate=LenOpaqueDate;
  cmd_t[0]=1; //SOH
  cmd_t[1]=1; //SOH
  cmd_t[2]=254;
  cmd_t[3]=13;
  cmd_t[4]=86;
  cmd_t[5]=cmdx;
  cmd_t[6]=0;
  cmd_t[7]=0;
  cmd_t[8]=0;
    for(int i=1;i<=sizeof(arg);i++)
    {
      cmd_t[8+i]=arg[i-1];
      }
  cmd_t[11]=LenOpaqueDate;
  cmd_t[12]=0;
  cmd_t[13]=0;
  cmd_t[14]=0;
  if(LenOpaqueDate > 1)
  {
  for(int i=0;i<_szopaquedate;i++)
    {
      cmd_t[15+i]=opaquedate[i];
      //Serial2.write(_szopaquedate);
     // Serial2.write(cmd_t[15+i]);
      }
      }
      cmd_t[14+_szopaquedate+1]=0;
      cmd_t[14+_szopaquedate+2]=0;
  //escrbir CtrlZ
  posicion_CtlZ=16+_szopaquedate;
  cmd_t[posicion_CtlZ+1]=26;

  No_zeros=  129-posicion_CtlZ; 
 
     for(int i=1; i<=No_zeros; i++)
     {
      cmd_t[posicion_CtlZ+1+i]=0;
      }
 //Serial2.println(cmd_t[130],HEX);
  for(int p=0; p<=127;p++)
  {
    datos[p]=cmd_t[3+p];
    }
  uint16_t g=CRC16.xmodem(datos, sizeof(datos));
  byte s[2];
   s[0]=*((uint8_t*)&(g)+1);
   s[1]=*((uint8_t*)&(g)+0);
       cmd_t[131]=s[0];
      cmd_t[132]=s[1];
      
  for(int j=0; j<=132; j++)
  {
      Serial1.write(cmd_t[j]);
      
  }

  }    

  void inicio(int comando)
  {


    //Cambiar_baud();
//    Serial2.write(lector_listo);
    if(lector_listo==67)
    {
    byte g_conf_baud[8]={0x04, 0x0,0x0,0x0,0x0, 0xE1, 0x0,0x0};
    byte g_conf_dev[]={0x40, 0, 0, 0, 0, 0, 0x64, 0, 0, 0, 0, 0, 0, 0, 0, 0, Trigger_Delay, _TimeOut, Override_Trigger, Override_HeartBeat_Display, Override_Default_LED, Match_Threshold, Set_Exposure_Mode, Select_PreProc, Select_Identifier, Select_Matcher, Select_Extractor, Select_Spoof_Model, Select_Template_Format, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x40, 0, 0, 0, 0, 0, 0, 0, 0x40, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};
    byte get_confg[]={128,0,0,0};      
      switch(comando)
      {
        case 1:
            arg[0]=0x0;
            arg[1]=0x0;
            //Get_No_Serial();
            generar_cmd_vector(85,arg,__opaquedate,0);    
        break;
        
        case 2:
            arg[0]=0x0;
            arg[1]=0x0;
            //Cambiar_baud();
            generar_cmd_vector(86,arg,g_conf_baud,8);
            
        break;
        
        case 3:
            arg[0]=0x0;
            arg[1]=0x0;
            generar_cmd_vector(0X4D,arg,g_conf_dev,68);
            //Configurar_dev();
            
        break;
        case 4:
            arg[0]=0x0;
            arg[1]=0x0;
            generar_cmd_vector(0X4C,arg,__opaquedate,0);
            //Configurar_dev();
            
        break;        
      
        case 5:
            //Arm_trigger();
            arg[0]=0x01;
            arg[1]=0x0;
            generar_cmd_vector(0X47,arg,__opaquedate,0);
            //x47//
        break;

        case 6: 
            //Acq_Status();
            arg[0]=0x0;
            arg[1]=0x0;
            generar_cmd_vector(0X48,arg,__opaquedate,0);                  
            break;

        case 7:
            //CMD_GET_SPOOF;
            arg[0]=0x0;
            arg[1]=0x0;
            generar_cmd_vector(0X43,arg,__opaquedate,0);              
            //CMD_GET_COMPOSITE_IMAGE();
            break;

        case 8:
            // CMD_GET_TEMPLATE
            arg[0]=0x0;
            arg[0]=0x0;
            generar_cmd_vector(0X45,arg,__opaquedate,0);            
        break;            

        case 9://PEDIR INFORMACIÓN DEL LECTOR
              //(hardware Revision No,firmware Revision No ,Spoof No Revision, PreProcesador Revision number, Matcher_rev_number)
            arg[0]=0x01;
            arg[1]=0x0;
            generar_cmd_vector(0X49,arg,get_confg,4);         
            //x47//
        break;          
            
      }
      
  }
  
  }
        void preparar_rx()
  {
//Serial2.println("o.....");
    if((lector_listo==6)&&(envio_EOT==false))
    {
      envio(true,4,0);
      envio_EOT=true;  // envío hecho por primera vez realizado
      }
    if((lector_listo==21)&&(envio_67==false))
    {
  //    Serial2.println("ok"); //DEBUG PARA MIRAR CONEXIÓN
      envio(true,67,0);
      envio_67=true;  // envío hecho por primera vez realizado
      activar_rx=true; // listo para recibir
      }
      
    }

    void preparar_rx_template()
    {
     if((lector_listo==6)&&(envio_EOT==false))
    {
      envio(true,4,0);
      envio_EOT=true;  // envío hecho por primera vez realizado
      }
    if((lector_listo==21)&&(envio_67==false))
    {
      envio(true,67,0);
      envio_67=true;  // envío hecho por primera vez realizado
      activar_rx_template=true; // listo para recibir
      
      }
      }




    
  void finalizar()
  {
    byte rx_buffer[128];
    byte recepcion[134];
    Serial1.readBytes(recepcion, 134);  //captura toda la informacion del buffer
    for(int i=0; i<=127; i++)
    {
      rx_buffer[i]=recepcion[4+i];
      //Serial2.write(rx_buffer[i]  );
      }

      
  uint16_t g=CRC16.xmodem(rx_buffer, sizeof(rx_buffer));
  byte s[2];
   s[0]=*((uint8_t*)&(g)+1); //toma la parte alta del hexa de 16 bits
   s[1]=*((uint8_t*)&(g)+0); ////toma la parte baja del hexa de 16 bits
      //Serial2.write(s[1]);
      
 //   Serial2.write(recepcion[134]);
    if (((recepcion[132]==s[0])&&(recepcion[133]==s[1])))
    {
      /* crc --> 42(2A) -- 225(E1) hacen parte del estado de lectura del Sensor <--  */
          if(rx_buffer[2]==0x45)  //recepcion de primera trama del template
          {
            deco_inf(3,rx_buffer);
            }
          if((rx_buffer[2]==0x43)||(rx_buffer[2]==0x49))//recibido spoof 
          
       {
        if(match2==false)
        {
           envio(true,0x18,0);}
           
           //Serial2.write(0xFF);
       }
      else
      {
          envio(true,6,0);
      }
      if(rx_buffer[2]==0x45)
      {
      //  activar_rx_template= true;
      finalizar_rx_tmp(rx_buffer);
        }

            if ((recepcion[133]==42)||(recepcion[133]==225)) //crc de respuesta de Status vuelve a pedir el Status hasta que el lector ya halla procesado el template
      {
        if (cnt_timeout<(TimeOut*20))
        {
         PROXIMO_ENVIO=5; // ArMAR TRIGGER
         cnt_timeout++;
        }
        else 
        {
          PROXIMO_ENVIO= 100;
          envio(true,0x18,1);
          Serial2.println("Fuera de tiempo");
          delay(100);
//          reset();
          }
      }

            if(rx_buffer[2]==0xE0)
      {
      //  activar_rx_template= true;
      
      Serial2.println("Lector Fail");
      //Serial2.println("Fuera de tiempo Fuera de tiempo Fuera de tiempo");
      delay(50);
      //reset();
//      digitalWrite(A6, LOW);
        //delay(5000);
        //digitalWrite(A6, HIGH);
        }
      recepcion[133]=0;
      
    }
    else 
      {
        if(match2==false)
        {
        (Serial1.write(0x18));} //Error en la información recibida
      }
   //Serial2.write(s[0]);

      delay(1);

    if((rx_buffer[2]==0x43)||(rx_buffer[2]==0x49))//recibido spoof correcto
      {
        //0x86 --- 0x44 Score de huella falsa = 5050
        //0x78 --- 0x98 Score de huella autentica = 5
        if(match2==false){
      envio(true,0x18,0);}
      //envio(true,0x043,0);
      delay(20);
      //EOT_rx =true;

      if (Spoof <=5550) // Nivel de Spoofing
      {
      
      solicitar_template =true;
      Spoof=5050;
      
      }
      else
      {
        if(match2==false){
        envio(true,0x18,1);}
      if (Enroll==true)
      {
        //Serial2.println("Fail Enrollment");
        delay(50);
        //reset_enroll();
        //reset();
        }
      
      }

      }
      if((rx_buffer[2]!=0x43)&&(rx_buffer[2]!=0x45)&&(rx_buffer[2]!=0x49))
      {  
       envio(true,6,0);
      }
      //
      activar_rx=false;
      activar_todo=false;
      envio_EOT=false;
      envio_67=false;
   // DECODIFICACIÓN DE INFORMACION PARA LOS RESPECTIVOS COMANDOS
      switch (rx_buffer[2])
      {
        case 0x55:          // Comando de Serial
               deco_inf(1,rx_buffer);
               break; 
        case 67:
               deco_inf(2,rx_buffer);  // decodificar Score Spoof
               //Serial2.write(0x88);
               break;
        case 0x49:
               deco_inf(4,rx_buffer);  // decodificar info device              
        break;               
        case 0x04:
               deco_inf(5,rx_buffer);  // decodificar ScoreMatch             
        break;                       
      }      
    }

  void finalizar_rx_tmp(byte rxTemp[])
  {
    
    activar_rx=false;
    byte rx_tmp_1[128];
    int16_t cnt_tmp2 =0;
    int16_t _crc_tmp_Xmodem =0;
    byte data[128];
    int time_tmp=0;
    int _No_tramas =0;
    int _pqt_template=0;
        //cnt_tmp    =0;
    byte Template[1300];
    byte Template2[1300];
    
    int detener;
    byte rx_tmp[133];
    
    //MATCH  MATCH  **********///


/// MATCH  --- MATCH *********///
    
    //Serial2.println(cnt_captura); //DEBUG
    if((Sz_template>116)&&(Sz_template<245))
    {_No_tramas=1;}    
    if((Sz_template>244)&&(Sz_template<373))
    {_No_tramas=2;}    
    if((Sz_template>372)&&(Sz_template<501))
    {_No_tramas=3;}    
    if((Sz_template>500)&&(Sz_template<629))
    {_No_tramas=4;}       
    if((Sz_template>628)&&(Sz_template<757))
    {_No_tramas=5;}
    else if((Sz_template>756)&&(Sz_template<885))
    {_No_tramas=6;}
    else if((Sz_template>884)&&(Sz_template<1013))
    {_No_tramas=7;}
    else if((Sz_template>1012)&&(Sz_template<1141))
    {_No_tramas=8;}    
    else if((Sz_template>1140)&&(Sz_template<1269))
    {_No_tramas=9;}    
    detener= _No_tramas-1;
    
    //****************** XMODEM ***************////
    
    //////////////////////////////////////////////
    for(int i=0; i<116; i++)
    {           
      Template[i]=rxTemp[12+i];
     //Serial.println(Template[i],DEC);         
      }
   while ( cnt_tmp<_No_tramas)
   {
    Serial1.readBytes(rx_tmp, 133);                         //captura toda la informacion del buffer

 
            for(int i=0; i<=127; i++)
            {
              rx_tmp_1[i]=rx_tmp[3+i];

              Template[cnt_tmp2+116]=rx_tmp[3+i];         // en la posicion 14 porque 
      
              
              cnt_tmp2++;
              data[i]=0;
            }

      uint16_t g=0;
      uint16_t h=0;
    //  g=CRC16.xmodem(rx_buffer, sizeof(rx_buffer));
      h=CRC16.xmodem(rx_tmp_1, sizeof(rx_tmp_1));
      byte s[2];
      byte t[2];
      s[0]=*((uint8_t*)&(g)+1);                          //toma la parte alta del hexa de 16 bits
      s[1]=*((uint8_t*)&(g)+0);                         ////toma la parte baja del hexa de 16 bits
            t[0]=*((uint8_t*)&(h)+1);                   //toma la parte alta del hexa de 16 bits
            t[1]=*((uint8_t*)&(h)+0);                   ////toma la parte baja del hexa de 16 bi

      if(cnt_tmp==detener)
      {
        envio(true,0x18,1); //Deja el dispositivo disponible
        }
      if (((rx_tmp[131]==t[0])&&(rx_tmp[132]==t[1])))
      {
        if (cnt_tmp < detener)
        {
            envio(true,0x06,0);                              
        }

        }
   cnt_tmp++;

   }

      if(cnt_tmp==_No_tramas)
      {
      activar_rx_template=false;
      activar_todo=false;
      envio_EOT=false;
      envio_67=false;
      
      captura_end=true;
      
      /// MATCH MATCH ****//

        
      }
     // deco_inf(4,Template); // imprimir todo el Template
      if( cnt_tmp >= _No_tramas)
      {
              activar_rx_template=false;
      activar_todo=false;
      envio_EOT=false;
      envio_67=false;
      lector_listo=0;


       

           if((capture==true))
           {
            //Cod_tmp_App(Template);
            //byte tmp2[]={0x23, 0x03, 0x00, 0x00, 0x46, 0x4D, 0x52, 0x00, 0x20, 0x32, 0x30, 0x00, 0x03, 0x23, 0x00, 0x35, 0x00, 0x17, 0x00, 0x00, 0x01, 0x18, 0x01, 0x60, 0x00, 0xC5, 0x00, 0xC5, 0x01, 0x00, 0x00, 0x00, 0x00, 0x24, 0x80, 0x56, 0x00, 0x17, 0x63, 0x0F, 0x40, 0xE7, 0x00, 0x23, 0x51, 0x0F, 0x40, 0xF6, 0x00, 0x44, 0x9F, 0x0E, 0x40, 0x83, 0x00, 0x46, 0x04, 0x0F, 0x40, 0x3B, 0x00, 0x49, 0x0C, 0x0F, 0x40, 0xA2, 0x00, 0x51, 0x5F, 0x0F, 0x80, 0x7C, 0x00, 0x59, 0x68, 0x0F, 0x80, 0x94, 0x00, 0x5E, 0x00, 0x0F, 0x40, 0x22, 0x00, 0x6C, 0x75, 0x0F, 0x40, 0x5A, 0x00, 0x86, 0x75, 0x0F, 0x40, 0xB5, 0x00, 0x87, 0x5B, 0x0F, 0x40, 0xCE, 0x00, 0x87, 0x47, 0x0F, 0x40, 0xF0, 0x00, 0x96, 0x8F, 0x0F, 0x40, 0xA0, 0x00, 0x97, 0xAC, 0x0F, 0x40, 0x7F, 0x00, 0xA2, 0x78, 0x0F, 0x40, 0x82, 0x00, 0xBD, 0x83, 0x0F, 0x40, 0x24, 0x00, 0xBF, 0x79, 0x0F, 0x80, 0xA9, 0x00, 0xC1, 0x7E, 0x0D, 0x40, 0x34, 0x00, 0xD7, 0x80, 0x0F, 0x40, 0x90, 0x00, 0xD5, 0x25, 0x0E, 0x40, 0x62, 0x00, 0xE7, 0x8A, 0x0F, 0x40, 0xE9, 0x00, 0xEA, 0x80, 0x0F, 0x40, 0xC6, 0x00, 0xEE, 0x74, 0x0F, 0x40, 0x90, 0x00, 0xFF, 0xB3, 0x0D, 0x40, 0xD5, 0x01, 0x03, 0x77, 0x0F, 0x40, 0xA9, 0x01, 0x06, 0x59, 0x0F, 0x40, 0xF6, 0x01, 0x0B, 0x81, 0x0F, 0x80, 0x68, 0x01, 0x0E, 0x96, 0x0F, 0x80, 0xB6, 0x01, 0x13, 0x6A, 0x0F, 0x80, 0x45, 0x01, 0x21, 0x8F, 0x04, 0x80, 0xD8, 0x01, 0x23, 0x76, 0x0F, 0x40, 0x87, 0x01, 0x27, 0x01, 0x0C, 0x40, 0x5C, 0x01, 0x2D, 0xA0, 0x08, 0x40, 0x45, 0x01, 0x32, 0x33, 0x01, 0x80, 0x3F, 0x01, 0x33, 0x9C, 0x01, 0x80, 0x91, 0x01, 0x37, 0x4E, 0x0F, 0x02, 0x2B, 0x01, 0x01, 0x02, 0x2B, 0x49, 0x43, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x35, 0x01, 0x02, 0x0D, 0x19, 0xF3, 0x03, 0x00, 0xE1, 0x12, 0x13, 0xC0, 0x03, 0x00, 0xC4, 0x13, 0x06, 0xFE, 0x08, 0x00, 0x84, 0x13, 0x7D, 0xC2, 0xC0, 0xC3, 0x51, 0x04, 0x00, 0x53, 0x18, 0x70, 0x59, 0x11, 0x00, 0xE6, 0x25, 0x8C, 0xC0, 0xC3, 0xFE, 0xC2, 0x5C, 0xC1, 0x7B, 0x7C, 0xC0, 0x0F, 0x00, 0xF0, 0x41, 0x97, 0x8B, 0xC2, 0x5C, 0x77, 0x5A, 0x0C, 0x00, 0x86, 0x43, 0xFA, 0x3D, 0x35, 0x33, 0xC0, 0x11, 0x00, 0x3C, 0x45, 0xE7, 0xFE, 0x4A, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0x30, 0xC2, 0xFB, 0xC3, 0x0B, 0x00, 0x7E, 0x48, 0x77, 0xC3, 0x45, 0x88, 0x5C, 0x0C, 0x00, 0x86, 0x49, 0xFD, 0x3D, 0xFE, 0x3D, 0xFD, 0x52, 0x04, 0x00, 0x36, 0x4C, 0x62, 0xC0, 0xC0, 0x0A, 0x00, 0xA8, 0x51, 0x09, 0xFF, 0xFF, 0xFF, 0x31, 0x47, 0x0D, 0x00, 0xA0, 0x55, 0x77, 0x8B, 0xC0, 0xC1, 0x71, 0x70, 0x0C, 0x00, 0x7A, 0x5B, 0x6D, 0xC0, 0xC2, 0x66, 0xC3, 0x51, 0xFE, 0x09, 0x00, 0x98, 0x5D, 0xFD, 0x29, 0x2A, 0xC0, 0x14, 0x00, 0x28, 0x67, 0xE7, 0xC1, 0xFD, 0x58, 0xC0, 0x3E, 0x40, 0xFF, 0x33, 0x47, 0x1B, 0x00, 0x5F, 0x83, 0xE4, 0x4B, 0xFD, 0xFF, 0xFE, 0xFF, 0xFD, 0xFE, 0xFE, 0xFF, 0xFE, 0xC0, 0xFF, 0xC0, 0xFE, 0xFF, 0xC1, 0xC0, 0xFD, 0xC1, 0xFD, 0xC1, 0xFF, 0xC0, 0x11, 0x00, 0xB3, 0x84, 0x89, 0xC3, 0xC4, 0xC2, 0xC0, 0x8C, 0x7B, 0xC3, 0xFE, 0x87, 0x0F, 0x00, 0x57, 0x86, 0x60, 0x7F, 0x72, 0xC0, 0xFF, 0xC2, 0xC1, 0xC0, 0xC2, 0xC3, 0x18, 0x00, 0xD0, 0x86, 0xA2, 0xC2, 0xC2, 0xC3, 0x9B, 0xC1, 0x86, 0x62, 0xC0, 0xC3, 0x59, 0x72, 0xC3, 0x07, 0x00, 0x5C, 0x8A, 0x56, 0x56, 0x6A, 0x11, 0x00, 0xBB, 0x8A, 0x1A, 0x2A, 0x2E, 0x4F, 0xFF, 0xFF, 0x3C, 0xFC, 0x18, 0x00, 0xCB, 0x8A, 0x9C, 0x9B, 0xC2, 0xC4, 0xC0, 0x8B, 0xC2, 0x6A, 0xC2, 0xFF, 0x77, 0xC2, 0x86, 0x05, 0x00, 0xB4, 0x8B, 0x83, 0x9F, 0x0A, 0x00, 0xD2, 0x8E, 0x2B, 0x38, 0x2B, 0x3F, 0x09, 0x00, 0xA3, 0x94, 0x00, 0xFE, 0xF9, 0xFE, 0xFE, 0xFE, 0x31, 0x05, 0x00, 0xF3, 0x96, 0x2D, 0xFE, 0x51, 0x09, 0x00, 0xED, 0x98, 0x34, 0xC0, 0xFD, 0xC1, 0xFF, 0xC0, 0x5B, 0x03, 0x00, 0x9B, 0x9A, 0x67, 0xC4, 0x0C, 0x00, 0xA3, 0x9B, 0x09, 0xFC, 0xFC, 0xFC, 0xC0, 0xFC, 0xFF, 0xFD, 0xFD, 0xFD, 0xFF, 0x06, 0x00, 0x7C, 0xA1, 0x5E, 0xC3, 0x6F, 0x11, 0x00, 0x82, 0xA5, 0x57, 0x77, 0xC3, 0x80, 0xC0, 0xC4, 0xC7, 0xC4, 0xC2, 0xC1, 0xC2, 0xC2, 0x0F, 0x00, 0x0F, 0xB7, 0xD6, 0x58, 0xC0, 0xFE, 0xFF, 0xC0, 0xFE, 0x4B, 0x44, 0x07, 0x00, 0x7F, 0xBE, 0x50, 0xA0, 0x71, 0x05, 0x00, 0x85, 0xBE, 0x46, 0x90, 0x0C, 0x00, 0xA7, 0xBE, 0x62, 0xC6, 0xC2, 0xCF, 0xCD, 0xC1, 0xC4, 0xC6, 0xCE, 0xC6, 0xC3, 0x03, 0x00, 0x21, 0xBF, 0x5E, 0xC4, 0x05, 0x00, 0x26, 0xC2, 0x50, 0xFF, 0x7B, 0x04, 0x00, 0xFF, 0xD0, 0x40, 0x6C, 0x09, 0x00, 0x31, 0xD8, 0x4F, 0xC1, 0xC0, 0x79, 0x83, 0x09, 0x00, 0x38, 0xDA, 0x46, 0xFF, 0x6F, 0xC2, 0x82, 0x09, 0x00, 0x5F, 0xEA, 0x43, 0x70, 0xC5, 0xC2, 0x96, 0x06, 0x00, 0x66, 0xEA, 0x3A, 0xC1, 0x89, 0x08, 0x00, 0xE7, 0xEC, 0x49, 0xC0, 0xFF, 0xFE, 0x3F, 0x07, 0x10, 0xD3, 0x04, 0x5A, 0xC0, 0xC0, 0x2E, 0x07, 0x10, 0xD9, 0x06, 0x53, 0xFF, 0x3E, 0xFD, 0x05, 0x10, 0xF2, 0x0D, 0x49, 0xFE, 0x60, 0x05, 0x10, 0xF9, 0x0D, 0x40, 0xFE, 0xFC, 0xC1, 0x05, 0x10, 0x6A, 0x13, 0x30, 0xC3, 0xC3, 0xC2, 0x04, 0x10, 0xB5, 0x15, 0x67, 0xFF, 0xFD, 0x03, 0x10, 0xD6, 0x27, 0x57, 0xC0, 0x03, 0x10, 0x5A, 0x2F, 0x24, 0xC2, 0x03, 0x10, 0x7B, 0x40, 0x96, 0xC0};
            
                /*for(int16_t i=0; i<(Sz_template); i++) // el 4 es el tamaño del template
                {
                //Serial.println(Sz_template);
                

                 }   */
               /*          for(int j=0; j<(Sz_template); j++)
        {
          
          i= Template[j];
          if(i<128)
          {
          switch (i)
          {
          case 10:
            Serial2.write(9);Serial2.write(0);
            break;
            case 13:
            Serial2.write(12);Serial2.write(0);
            break;
            default:
            Serial2.write(0);Serial2.write(i);Serial1.write(i);
            break;
          }
          }
          if(i>127)
          {
            i=i-128;
                    switch(i)
          {
            case 127:
            Serial2.write(126);Serial2.write(i);Serial1.write(i);
            break;
            case 9:
            Serial2.write(14);Serial2.write(127);
            break;
            case 12:
            Serial2.write(15);Serial2.write(127);
            break;            
            default:
            Serial2.write(127);Serial2.write(i+1);Serial1.write(i);
            break;
          }

          }
          
            }*/

                 sensor_enable=true;
                 Serial2.println("Fingerprint Captured");    
                 //delay(20);
                 Serial2.readBytes(Template2,1300);
                 
                 
            }


        
      }
      cnt_matcher=1;

      if((Template[4]==0x46)&&(Template[5]==0x4D)&&(Template[6]==0x52))
      {Make_Match(Template,Template);         
      matcher=true;
       inRecepcion=0;
       }
      else{Serial2.println("Error Template");ACT=false;}
    }
    void Make_Match(byte Template1[], byte Template2[])
    {
      int16_t _sz_Temp1_M=0;
      int16_t _sz_Temp2_M=0;
      int16_t _sz_TempT=0;
      int16_t total=0;


            _sz_Temp1_M = _sz_Temp1_M<<8|Template1 [1];
            _sz_Temp1_M = _sz_Temp1_M<<8|Template1 [0];
            _sz_Temp2_M = _sz_Temp2_M<<8|Template2[1];
            _sz_Temp2_M = _sz_Temp2_M<<8|Template2[0];
            
            _sz_TempT= _sz_Temp1_M+ (_sz_Temp2_M+8);
             

                   byte t[2];
      byte s[2];
      byte u[2];                   

            t[0]=*((uint8_t*)&(_sz_TempT)+1); //toma la parte alta del hexa de 16 bits
            t[1]=*((uint8_t*)&(_sz_TempT)+0); ////toma la parte baja del hexa de 16 bits            
            int16_t _sz_cmd_Match = _sz_TempT+15;
            
            byte TemplateT[_sz_TempT+3];
            byte cmd_Match[_sz_cmd_Match];
            byte data[128];
            int16_t h=0;
             


          
           for(int16_t i=0; i<=(_sz_TempT+2);i++ )
            {
            if(i<= (_sz_Temp1_M+3))
            {
            TemplateT[i]=Template1[i];
            
            }
            if(i > (_sz_Temp1_M+3))
            {
              TemplateT[i]=Template2[i-(_sz_Temp1_M+4)];
            
            }
            
            }
              
  
           cmd_Match[0]=13;
            cmd_Match[1]=86;
            cmd_Match[2]=4;  //cmd
            cmd_Match[3]=0;
            cmd_Match[4]=0;
            cmd_Match[5]=0;
            cmd_Match[6]=0; //arg
            cmd_Match[7]=0; //arg
            cmd_Match[8]=t[1];
            cmd_Match[9]=t[0];
            cmd_Match[10]=0;
            cmd_Match[11]=0;  

            

                   
            for(int16_t i=0; i<=_sz_TempT+2; i++)
            {cmd_Match[12+i]=TemplateT[i];}
     //       Serial2.println(_sz_TempT); //debug tamaños de template y envio de comando match
     //       Serial2.println(_sz_Temp1_M); //debug tamaños de template y envio de comando match
     //       Serial2.println(_sz_Temp2_M); //debug tamaños de template y envio de comando match            
            int No_tramas=8;
             if(((_sz_TempT+12)>1024)&&((_sz_TempT+12)<=1152))
            {No_tramas=9;}

            else if(((_sz_TempT+12)>1152)&&((_sz_TempT+12)<=1280))
            {No_tramas=10;}
            
            else if(((_sz_TempT+12)>1280)&&((_sz_TempT+12)<=1408))
            {No_tramas=11;}

            else if(((_sz_TempT+12)>1408)&&((_sz_TempT+12)<=1536))
            {No_tramas=12;}

            else if(((_sz_TempT+12)>1536)&&((_sz_TempT+12)<=1664))
            {No_tramas=13;}
            
            else if(((_sz_TempT+12)>1664)&&((_sz_TempT+12)<=1792))
            {No_tramas=14;}
            
            else if(((_sz_TempT+12)>1792)&&((_sz_TempT+12)<=1920))
            {No_tramas=15;}  
            else if(((_sz_TempT+12)>1920)&&((_sz_TempT+12)<=2048))
            {No_tramas=16;}              
            else if(((_sz_TempT+12)>2048)&&((_sz_TempT+12)<=2176))
            {No_tramas=17;}                          
            else if(((_sz_TempT+12)>2176)&&((_sz_TempT+12)<=2304))
            {No_tramas=18;}                                      
            else if(((_sz_TempT+12)>2304)&&((_sz_TempT+12)<=2432))
            {No_tramas=19;}                          
             
       //      delay(2);
                   
             envio(true,0x15,1);
         //    Serial2.println(_sz_TempT); //debug tamaños de template y envio de comando match

            for(int i=0; i<No_tramas;i++)
            {
              
                Serial1.write(1);
                Serial1.write(1+i);               
                Serial1.write(254-i);
              for(int j=0; j<=127;j++)
              {
                total=j+(128*i);
                //Serial2.write(cmd_Match[j+(128*i)]);

                if((total)>=_sz_cmd_Match)
                {Serial1.write(0);data[j]=0;}
                
                else if ((total)<_sz_cmd_Match)
                {
                  Serial1.write(cmd_Match[total]);
                  data[j]=cmd_Match[total];
                  }
                
                }
                  h=CRC16.xmodem(data, sizeof(data));


                  u[0]=*((uint8_t*)&(h)+1);                   //toma la parte alta del hexa de 16 bits
                  u[1]=*((uint8_t*)&(h)+0);                   ////toma la parte baja del hexa de 16 bi       
                Serial1.write(u[0]);                           
                Serial1.write(u[1]);   
                                                        
              }
            
      }
      

    void deco_inf(int cmd,byte data[])
    //void deco_inf()
    {

      int cmd_rx =0;
      cmd_rx=cmd;
      int32_t _Sz_data=0;
      int16_t _H_rev_No=0;  // Numero de revisión de hardware
      int16_t _F_rev_No=0;
      int16_t _Spoof_rev_No=0;
      int16_t _crc_spoof_Xmodem=0;

      byte t[2];
      byte rx[128];
      byte paquete[2];
      paquete[0]=0x50;
      paquete[1]=0x51;
      paquete[2]=0x52;
      long prueba;
      prueba = prueba<<8|paquete[0];
      prueba = prueba<<8|paquete[1];
      prueba = prueba<<8|paquete[2];
      _Sz_data = _Sz_data<<8|data[11];
      _Sz_data = _Sz_data<<8|data[10];
      _Sz_data = _Sz_data<<8|data[9];
      _Sz_data = _Sz_data<<8|data[8];
      byte _data_SN[8];
      byte _data_Spoof[4];
               int32_t _Spoof_Score;
               
            byte _Spoof[4]; 
            int16_t _sz_template=0;     
            ///////////////////////////////////////////MATCH
            
            byte _data_SMATCH[8];
            

      for(int i=0; i<128; i++)                     
      {
        rx[i]=data[i];
        }
      _crc_spoof_Xmodem=CRC16.xmodem(rx, sizeof(rx));
            t[0]=*((uint8_t*)&(_crc_spoof_Xmodem)+1); //toma la parte alta del hexa de 16 bits
            t[1]=*((uint8_t*)&(_crc_spoof_Xmodem)+0); ////toma la parte baja del hexa de 16 bi                    
      switch (cmd_rx)
      {
       case 5:
         for(int i=0; i<=7; i++)
         {
         _data_SMATCH[i]= data[12+i];     
          }
           score_match= score_match<<8|_data_SMATCH[3];
           score_match= score_match<<8|_data_SMATCH[2];
           score_match= score_match<<8|_data_SMATCH[1];
           score_match= score_match<<8|_data_SMATCH[0];
                         



              if(score_match>Threshold)
              {
              Serial2.println("Match Successfull");

              //digitalWrite(LED_val, LOW);
              ACT =false;
              //contadorFP();
              access=false;
              }
              else{Serial2.println("Match Denied");
              ACT =false;

              }
              Serial2.print("Score Match: ");
              Serial2.println(score_match);
            //contador();
            
           //reset();
              
  
       break;
        
        case 1:         //captura del Serial
      
          
         for(int i=0; i<=7; i++)
         {
         _data_SN[i]= data[12+i];     
          }
           _SN= _SN<<8|_data_SN[7];
           _SN= _SN<<8|_data_SN[6];
           _SN= _SN<<8|_data_SN[5];
           _SN= _SN<<8|_data_SN[4];

            if(Xmodem==false)      //NO BORRAR Activar solo cuando se vaya a usar Xmodem
            {
              
            Serial2.println("SN: ");
            Serial2.println(_SN,DEC);    
              }            
             
          break;
          
          case 2:     // Spoof de la huella 

                        _data_Spoof[0]= data[12];
            _data_Spoof[1]= data[13];
            _data_Spoof[2]= data[14];
            _data_Spoof[3]= data[15];
            _Spoof_Score = _Spoof_Score<<8|_data_Spoof[3];
            _Spoof_Score = _Spoof_Score<<8|_data_Spoof[2];
            _Spoof_Score = _Spoof_Score<<8|_data_Spoof[1];
            _Spoof_Score = _Spoof_Score<<8|_data_Spoof[0];
            Spoof = Spoof<<8|_data_Spoof[3];
            Spoof = Spoof<<8|_data_Spoof[2];
            Spoof = Spoof<<8|_data_Spoof[1];
            Spoof = Spoof<<8|_data_Spoof[0];         
          break;
 
          case 3:

            Sz_template = Sz_template<<8|data[11];
            Sz_template = Sz_template<<8|data[10];
            Sz_template = Sz_template<<8|data[9];
            Sz_template = Sz_template<<8|data[8];     
            //Serial2.println(Sz_template);
        break;

          case 4:   //deco info_device
           
          
          _Spoof_rev_No =_Spoof_rev_No<<8|data[23];
          _Spoof_rev_No =_Spoof_rev_No<<8|data[22];
          _F_rev_No     =_F_rev_No<<8|data[21];
          _F_rev_No     =_F_rev_No<<8|data[20];
          _H_rev_No     =_H_rev_No<<8|data[19];
          _H_rev_No     =_H_rev_No<<8|data[18];
         break;
          


      }

      }
      void captura()
      {
        
        sensor_enable=false;
        enviar_comando_template=false;
        activar_todo=true;
        PROXIMO_ENVIO = 5;
        envio(true,21,1);
        lector_listo=0;
        inRecepcion=0;
        captura_end=false;
        cnt_timeout=0;             
        cnt_tmp=0;

        capture=true;
           
        }      
              void setUpLector()
              {
                        PROXIMO_ENVIO = 3;
                    activar_todo=true;
                    envio(true,21,1);
                    lector_listo=0;
                     inRecepcion=0;
                     mcu_Peticion="";
                }        
void loop() {
             // wait for a second
/*if (setupd==true)
{
  timer++;
  
  Serial2.println(timer);
  }
  */
if(timer==2500)

{

  digitalWrite(LED_val,LOW);
  digitalWrite(p_Lector,HIGH);
     setUpLector();
     Serial2.println("Device setup");

     setupd=false;
     timer = 0;

  }             
serialEvent1();
serialEvent2();
  //Serial1.println("Hola Mundo");
}
