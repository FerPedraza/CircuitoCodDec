
void setup() {
  // Declaracion de variables
  pinMode(22,INPUT);
  pinMode(23,INPUT);
  pinMode(24,OUTPUT);
  pinMode(25,OUTPUT);
  pinMode(26,OUTPUT);
  pinMode(27,OUTPUT);
  pinMode(28,OUTPUT);
  pinMode(29,OUTPUT);
  pinMode(30,OUTPUT);
  pinMode(31,OUTPUT);
  pinMode(32,OUTPUT);
  pinMode(33,INPUT);
  pinMode(34,INPUT);
  pinMode(35,INPUT);
  pinMode(36,INPUT);
  pinMode(37,INPUT);
  pinMode(38,INPUT);
  pinMode(39,INPUT);
  pinMode(40,INPUT);
  pinMode(41,OUTPUT);
  pinMode(42,INPUT);

  pinMode(43,OUTPUT);
  pinMode(44,OUTPUT);
  pinMode(45,OUTPUT);
  pinMode(46,OUTPUT);
  pinMode(47,OUTPUT);
  pinMode(48,OUTPUT);
  pinMode(49,OUTPUT);
  pinMode(50,OUTPUT);
  pinMode(51,OUTPUT);
  pinMode(52,OUTPUT);
  pinMode(53,OUTPUT);
}
byte data[3];
byte code[7];
byte r[7];
byte s[4];
byte e[7];
byte bitError[7];
byte dataErrorGen[7];
byte dataFromCoder[7];
byte rCorregido[7];
int tiempo = 600;
void loop() {
  // Recoje los datos de entrada
  int cont = 0;
  while (cont < 3){
    if(digitalRead(23)){
      delay(tiempo);
      data[cont]=digitalRead(22); 
      cont++;
    }
  }
  // Muestra los datos de entrada
  for (int i = 0; i <4; i++) {
    digitalWrite(24,data[i]);
    delay(tiempo);
  }
  
  // Hace el coder y lo muestra
  code[0] = data[0];
  delay(tiempo);
  digitalWrite(25,code[0]);
  code[1] = data[1];
  delay(tiempo);
  digitalWrite(26,code[1]);
  code[2] = data[2];
  delay(tiempo);
  digitalWrite(27,code[2]);
  code[3] = data[0] ^ data[2];
  delay(tiempo);
  digitalWrite(28,code[3]);
  code[4] = data[1] ^ data[2];
  delay(tiempo);
  digitalWrite(29,code[4]);
  code[5] = data[0] ^ data[1] ^ data[2];
  delay(tiempo);
  digitalWrite(30,code[5]);
  code[6] = data[0] ^ data[1];
  delay(tiempo);
  digitalWrite(31,code[6]);
  
  //Se realiza el envio del coder al generador de error
  for (int i = 0; i <7; i++) {
    digitalWrite(32,code[i]);
    delay(tiempo);
    dataFromCoder[i]=digitalRead(33); 
  }
  //Se lee y se hace la suma del error generado
  for (int i = 0; i <7; i++) {
    bitError[i]=digitalRead(i+34); 
  }
  for (int i = 0; i <7; i++) {
    dataErrorGen[i]=dataFromCoder[i] ^ bitError[i];
  }
  delay(tiempo*2);
  //envio de los datos con error
  for (int i = 0; i <7; i++) {
    digitalWrite(41,dataErrorGen[i]);
    delay(tiempo);
    r[i]=digitalRead(42); 
  }
  //CALCULO DE SINDROME
  s[0] = r[0] ^ r[2] ^ r[3];
  s[1] = r[1] ^ r[2] ^ r[4];
  s[2] = r[0] ^ r[1] ^ r[2] ^ r[5];
  s[3] = r[0] ^ r[1] ^ r[6];
  digitalWrite(43,s[0]);
  digitalWrite(44,s[1]);
  digitalWrite(45,s[2]);
  digitalWrite(46,s[3]);
  //Patron de error
  e[0] = s[0] & ~s[1] & s[2] & s[3];
  e[1] = ~s[0] & s[1] & s[2] & s[3]; 
  e[2] = s[0] & s[1] & s[2] & ~s[3]; 
  e[3] = (s[0] & ~s[1] & ~s[2] & ~s[3]) ^ (s[0] & s[1] & ~s[2] & ~s[3]); 
  e[4] = (~s[0] & s[1] & ~s[2] & ~s[3]) ^ (s[0] & s[1] & ~s[2] & ~s[3]); 
  e[5] = (~s[0] & ~s[1] & s[2] & ~s[3]) ^ (~s[0] & ~s[1] & s[2] & s[3]); 
  e[6] = (~s[0] & ~s[1] & ~s[2] & s[3]) ^ (~s[0] & ~s[1] & s[2] & s[3]);
  
  for (int i = 0; i <7; i++) {
    delay(tiempo);
    rCorregido[i] = e[i] ^ r[i];
    digitalWrite(47+i,rCorregido[i]);
  }
  

  
}
