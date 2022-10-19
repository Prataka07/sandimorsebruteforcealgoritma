int ledhijau=11;//pinlampu 
int ledmerah=12;
int titikButton=2;//titikbutton
int garisButton=3;//garisbutton
int buzzer=8;

int characterAscii=0;//karakter
int mulaiposisi=0, 
	akhirposisi=0;//mulai posisi - akhir posisi
int mulaiposisi1=0, 
	akhirposisi1=0;//mulai posisi1 - akhir posisi1
int bagiangarisButton=0;//statusgarisbutton
int bagiantitikButton=0;//statustitikbutton

#define karakter 70//array dari ascci untuk morse code karakter 
String sandimorse="";//sandimorse
String karaktersandi="";
String text="";
String data[karakter]={
  "-.-.--", // 33 - !
  ".-..-.", // 34 - "
  "",       // 35 - #
  "...-..-",// 36 - $
  "",       // 37 - %
  ".-...",  // 38 - &
  ".----.", // 39 - '
  "-.--.",  // 40 - (
  "-.--.-", // 41 - )
  "",       // 42 - *
  ".-.-.",  // 43 - +
  "--..--", // 44 - ,
  "-....-", // 45 - -
  ".-.-.-", // 46 - .
  "-..-.",  // 47 - /
  "-----",  // 48 - 0
  ".----",  // 49 - 1
  "..---",  // 50 - 2
  "...--",  // 51 - 3
  "....-",  // 52 - 4
  ".....",  // 53 - 5
  "-....",  // 54 - 6
  "--...",  // 55 - 7
  "---..",  // 56 - 8
  "----.",  // 57 - 9
  "---...", // 58 - :
  "-.-.-.", // 59 - ;
  "",       // 60 - <
  "-...-",  // 61 - =
  "",       // 62 - >
  "..--..", // 63 - ?
  ".--.-.", // 64 - @
  ".-",     // 65 - A
  "-...",   // 66 - B
  "-.-.",   // 67 - C
  "-..",    // 68 - D
  ".",      // 69 - E
  "..-.",   // 70 - F
  "--.",    // 71 - G
  "....",   // 72 - H
  "..",     // 73 - I
  ".---",   // 74 - J
  "-.-",    // 75 - K
  ".-..",   // 76 - L
  "--",     // 77 - M
  "-.",     // 78 - N
  "---",    // 79 - O
  ".--.",   // 80 - P
  "--.-",   // 81 - Q
  ".-.",    // 82 - R
  "...",    // 83 - S
  "-",      // 84 - T
  "..-",    // 85 - U
  "...-",   // 86 - V
  ".--",    // 87 - W
  "-..-",   // 88 - X
  "-.--",   // 89 - Y
  "--..",   // 90 - Z
  "",       // 91 - [
  "",       // 92 - \.
  "",       // 93 - ]
  "",       // 94 - ^
  "..--.-" // 95 - _
};

        
void setup() {

pinMode(ledhijau, OUTPUT);
pinMode(ledmerah, OUTPUT);
pinMode(titikButton, INPUT);
pinMode(garisButton, INPUT);
pinMode(buzzer, OUTPUT);
Serial.begin(9600);

Serial.println("\nMasukan 1 untuk enter  ");
Serial.println("\nMasukan \ untuk spasi  ");
Serial.println("\n\nSandi Morse ");

}

void hijau()
{
  digitalWrite(ledhijau, HIGH);
}

void merah()
{
  digitalWrite(ledmerah, HIGH);
}

void suara()
{
  digitalWrite(buzzer, HIGH);
}

void mati()
{
  digitalWrite(ledhijau, LOW);
  digitalWrite(ledmerah, LOW);
  digitalWrite(buzzer, LOW);
}

//prosess pada hardware

void proses()
{
  
  bagiantitikButton=digitalRead(titikButton);
  bagiangarisButton=digitalRead(garisButton);
  
  if(bagiangarisButton == HIGH)
  {
    sandimorse=sandimorse+("-"); // menyimpan string dalam sandi morse variabel dengan bantuan fungsi penggabungan
    Serial.print("-");//pengguna menekan sandi
    merah();
    suara();
    delay(1000);
  }
  else if(bagiantitikButton == HIGH)
  {
   sandimorse=sandimorse+(".");
   Serial.print(".");
   delay(200);
   hijau();
   suara();
  }
  else if(bagiangarisButton==HIGH && bagiantitikButton==HIGH)
  {
    sandimorse=sandimorse+(" ");
    mati();
    delay(200);
  }
  else
  {
    mati();
    delay(200);
  }

}

char konvmenjadikarakter(String karaktersandi) //bruteforce
{
  
  for(int i=0; i<karakter; i++)
  {
   	if(karaktersandi == data[i])
    {
      characterAscii = i+33;//ascii dari urutan ke 33
      break;
    }
  }
  return characterAscii;

}

void mengeksposdata(String data) //string matching
{
        data.concat('|'); // Menempatkan | di akhir kata untuk menyederhanakan pemrosesan lebih lanjut

        akhirposisi=data.indexOf('|');
        // while(akhirposisi != -1)
        // {
        //   mulaiposisi=akhirposisi+1;
        //   akhirposisi=data.indexOf('|', mulaiposisi);
        //   karaktersandi=data.substring(mulaiposisi, akhirposisi);
        //   text=text+konvmenjadikarakter(karaktersandi);
        // }
        
        // while( akhirposisi<data.length() )
        // {
        //   karaktersandi=data.substring(mulaiposisi, akhirposisi);
        //   text.concat(konvmenjadikarakter(karaktersandi));
        //   mulaiposisi=akhirposisi+1;
        //   karaktersandi="";
        //   if(mulaiposisi == data.length() )
        //   {
        //     break;
        //   }
        //   akhirposisi=data.indexOf('|', mulaiposisi);   
        //  } 
 
        while(akhirposisi < data.length()) //Loop untuk mengekstraksi Kode morse karakter tunggal dari rangkaian kata  
        {
          text.concat(konvmenjadikarakter(data.substring(mulaiposisi, akhirposisi)));// ditambahkan data.substring
          
          mulaiposisi=akhirposisi+1;
          
          if(mulaiposisi == data.length())
          {
            break;
          }
          akhirposisi=data.indexOf('|', mulaiposisi);
        }
                
        
        Serial.print(text);
        Serial.print(" ");
        mulaiposisi=0;
        akhirposisi=0;
        text="";    

  
}

void loop() 
{
while(Serial.available() > 0 ) 
{
      int ascii=Serial.read();
	  // if(ascii == 1)
      // {
      //   proses();
      // }
      // else if(ascii == 92)
      // {
      //   sandimorse=sandimorse+("\");
      //   Serial.print("\");
      //   mengeksposdata(sandimorse);
      //   sandimorse="";
      // }
      // else
      // {
      //   sandimorse=sandimorse+("#");
      //   Serial.print("#");
      //   mengeksposdata(sandimorse);
      //   sandimorse="";
      // }
  

      switch(ascii)
      {
        case 49: //

        Serial.print("\n");
        sandimorse=sandimorse+("#");

         Serial.print("\nTerjemahan Sandi Morse :  ");
         
        akhirposisi1=sandimorse.indexOf('#');

        while(akhirposisi1 < sandimorse.length() ) //string matching
        {
            mengeksposdata(sandimorse.substring(mulaiposisi1, akhirposisi1)); // fungsi yang mengubah data sandi morse menjadi angka, huruf, dan simbol.
           mulaiposisi1=akhirposisi1+1;
           if(mulaiposisi1 == sandimorse.length() )
           {
              break; 
           }
           akhirposisi1= sandimorse.indexOf('#', mulaiposisi1);
        }
        mulaiposisi1=0;
        akhirposisi1=0;

        text=""; //mengubah terjemahan baru   
        sandimorse="";
        Serial.println("\n\nMasukan Kode Morse :");
        
              
        break;

        case 92: // 92 data ascii ditombol keyboard \
        
        sandimorse=sandimorse+("|");
        Serial.print("|");
        delay(200);
        
        break;

        case 51: // 51 data ascii dari keyboard 2
          
        sandimorse=sandimorse+("#");
        Serial.print("#");
        delay(200);
        
        break;
        
      }
      
}

proses();

}


