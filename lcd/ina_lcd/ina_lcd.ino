#define RS_PIN 4
#define E_PIN 7
#define DB4_PIN 8
#define DB5_PIN 9
#define DB6_PIN 10
#define DB7_PIN 11

#define Base_value 15

#define Min_V 13500 //バッテリーの駆動する最低値
#define Max_V 21000 //バッテリーの駆動する最大値

#include <LiquidCrystal.h>;


/*
  Texas Instruments INA226 Control sample
  tomozh@gmail.com

  2031.09.03 fix power miscalculation bug
  2013.03.16 1st release
*/

#include <Wire.h>

#define NELEMS(arg) (sizeof(arg) / sizeof((arg)[0]))

const int   INA226_ADDR         = 0x40;                 // INA226 I2C Address (A0=A1=GND)
const word  INA226_CAL_VALUE    = 0x0A00;               // INA226 Calibration Register Value

// INA226 Registers
#define INA226_REG_CONGIGURATION_REG            0x00    // Configuration Register (R/W)
#define INA226_REG_SHUNT_VOLTAGE                0x01    // Shunt Voltage (R)
#define INA226_REG_BUS_VOLTAGE                  0x02    // Bus Voltage (R)
#define INA226_REG_POWER                        0x03    // Power (R)
#define INA226_REG_CURRENT                      0x04    // Current (R)
#define INA226_REG_CALIBRATION                  0x05    // Calibration (R/W)
#define INA226_REG_MASK_ENABLE                  0x06    // Mask/Enable (R/W)
#define INA226_REG_ALERT_LIMIT                  0x07    // Alert Limit (R/W)
#define INA226_REG_DIE_ID                       0xFF    // Die ID (R)

// Operating Mode (Mode Settings [2:0])
#define INA226_CONF_MODE_POWER_DOWN             (0<<0)  // Power-Down
#define INA226_CONF_MODE_TRIG_SHUNT_VOLTAGE     (1<<0)  // Shunt Voltage, Triggered
#define INA226_CONF_MODE_TRIG_BUS_VOLTAGE       (2<<0)  // Bus Voltage, Triggered
#define INA226_CONF_MODE_TRIG_SHUNT_AND_BUS     (3<<0)  // Shunt and Bus, Triggered
#define INA226_CONF_MODE_POWER_DOWN2            (4<<0)  // Power-Down
#define INA226_CONF_MODE_CONT_SHUNT_VOLTAGE     (5<<0)  // Shunt Voltage, Continuous
#define INA226_CONF_MODE_CONT_BUS_VOLTAGE       (6<<0)  // Bus Voltage, Continuous
#define INA226_CONF_MODE_CONT_SHUNT_AND_BUS     (7<<0)  // Shunt and Bus, Continuous (default)

// Shunt Voltage Conversion Time (VSH CT Bit Settings [5:3])
#define INA226_CONF_VSH_140uS                   (0<<3)  // 140us
#define INA226_CONF_VSH_204uS                   (1<<3)  // 204us
#define INA226_CONF_VSH_332uS                   (2<<3)  // 332us
#define INA226_CONF_VSH_588uS                   (3<<3)  // 588us
#define INA226_CONF_VSH_1100uS                  (4<<3)  // 1.1ms (default)
#define INA226_CONF_VSH_2116uS                  (5<<3)  // 2.116ms
#define INA226_CONF_VSH_4156uS                  (6<<3)  // 4.156ms
#define INA226_CONF_VSH_8244uS                  (7<<3)  // 8.244ms

// Bus Voltage Conversion Time (VBUS CT Bit Settings [8:6])
#define INA226_CONF_VBUS_140uS                  (0<<6)  // 140us
#define INA226_CONF_VBUS_204uS                  (1<<6)  // 204us
#define INA226_CONF_VBUS_332uS                  (2<<6)  // 332us
#define INA226_CONF_VBUS_588uS                  (3<<6)  // 588us
#define INA226_CONF_VBUS_1100uS                 (4<<6)  // 1.1ms (default)
#define INA226_CONF_VBUS_2116uS                 (5<<6)  // 2.116ms
#define INA226_CONF_VBUS_4156uS                 (6<<6)  // 4.156ms
#define INA226_CONF_VBUS_8244uS                 (7<<6)  // 8.244ms

// Averaging Mode (AVG Bit Settings[11:9])
#define INA226_CONF_AVG_1                       (0<<9)  // 1 (default)
#define INA226_CONF_AVG_4                       (1<<9)  // 4
#define INA226_CONF_AVG_16                      (2<<9)  // 16
#define INA226_CONF_AVG_64                      (3<<9)  // 64
#define INA226_CONF_AVG_128                     (4<<9)  // 128
#define INA226_CONF_AVG_256                     (5<<9)  // 256
#define INA226_CONF_AVG_512                     (6<<9)  // 512
#define INA226_CONF_AVG_1024                    (7<<9)  // 1024

// Reset Bit (RST bit [15])
#define INA226_CONF_RESET_ACTIVE                (1<<15)
#define INA226_CONF_RESET_INACTIVE              (0<<15)

LiquidCrystal lcd(RS_PIN, E_PIN, DB4_PIN, DB5_PIN, DB6_PIN, DB7_PIN);

void setup() {

  Wire.begin();
  Serial.begin(9600);

  setupRegister();

  lcd.begin(20, 4);
  //lcd.print("(^-^*)/ hello,world!");
  delay(3000);
}

/*
  Texas Instruments INA226 Control sample
  tomozh@gmail.com

  2031.09.03 fix power miscalculation bug
  2013.03.16 1st release
*/



static void writeRegister(byte reg, word value)
{
  Wire.beginTransmission(INA226_ADDR);
  Wire.write(reg);
  Wire.write((value >> 8) & 0xFF);
  Wire.write(value & 0xFF);
  Wire.endTransmission();
}

static void setupRegister(void)
{
  writeRegister(INA226_REG_CONGIGURATION_REG,
                INA226_CONF_RESET_INACTIVE
                | INA226_CONF_MODE_CONT_SHUNT_AND_BUS
                | INA226_CONF_VSH_1100uS
                | INA226_CONF_VBUS_1100uS
                | INA226_CONF_AVG_64
               );

  writeRegister(INA226_REG_CALIBRATION, INA226_CAL_VALUE);
}

static word readRegister(byte reg)
{
  word res = 0x0000;

  Wire.beginTransmission(INA226_ADDR);
  Wire.write(reg);

  if (Wire.endTransmission() == 0) {
    if (Wire.requestFrom(INA226_ADDR, 2) >= 2) {
      res = Wire.read() * 256;
      res += Wire.read();
    }
  }

  return res;
}

typedef struct tagREG_INFO {
  byte  reg;
  const char* name;
} REG_INFO;

const static REG_INFO   st_aRegs[] = {
  { INA226_REG_CONGIGURATION_REG,   "Configuration Register"    },
  { INA226_REG_SHUNT_VOLTAGE,       "Shunt Voltage"             },
  { INA226_REG_BUS_VOLTAGE,         "Bus Voltage"               },
  { INA226_REG_POWER,               "Power"                     },
  { INA226_REG_CURRENT,             "Current"                   },
  { INA226_REG_CALIBRATION,         "Calibration"               },
  { INA226_REG_MASK_ENABLE,         "Mask/Enable"               },
  { INA226_REG_ALERT_LIMIT,         "Alert Limit"               },
  { INA226_REG_DIE_ID,              "Die ID"                    },
};

static void dumpRegisters(void)
{
  int i;
  const REG_INFO* pInfo;
  static word REGS[NELEMS(st_aRegs)];
  static char  buf[64];

  for (i = 0; i < NELEMS(REGS); i++) {
    pInfo = &st_aRegs[i];
    REGS[i] = readRegister(pInfo->reg);
  }

  Serial.println("---INA226 Registers ---");

  for (i = 0; i < NELEMS(REGS); i++) {
    pInfo = &st_aRegs[i];
    snprintf(buf, NELEMS(buf), "%24s (%02Xh) : %04Xh (%u)", pInfo->name, pInfo->reg, REGS[i], REGS[i]);
    Serial.println(buf);
  }
}


long measure()
{
  char  buf[64];
  long  voltage;   // Bus Voltage (mV)
  short current;   // Current (mA)
  long  power;     // Power (uW)

  voltage  = (long)((short)readRegister(INA226_REG_BUS_VOLTAGE)) * 1250L;    // LSB=1.25mV
  current  = (short)readRegister(INA226_REG_CURRENT);
  power    = (long)readRegister(INA226_REG_POWER) * 25000L;                  // LSB=25mW

  Serial.println();
  snprintf(buf, NELEMS(buf)
           , "V:%5ldmV, I:%5dmA, P:%5ldmW"
           , (voltage + (1000 / 2)) / 1000
           , current
           , (power + (1000 / 2)) / 1000
          );

  Serial.println(buf);

  dumpRegisters();

  delay(1000);
  return voltage;
}

// ■を表示
void disp(int col, int row) {
  lcd.setCursor(col, row);
  lcd.print("\xff\xff");
}

// pcのバッテリー値表示
void pc_disp(long voltage) {
  lcd.setCursor(1, 0);
  lcd.print("[PC]    ");
  lcd.print((voltage + (1000 / 2)) / 1000);
  lcd.print("\x6d\x56");
}
// 台車のバッテリー値表示(失敗した)
void per_disp(float pc_per) {
  lcd.setCursor(1, 1);
  lcd.print("[\xc9\xba\xd8]  ");
  lcd.print(pc_per);
  lcd.print("\x25");
}

//メイン文
void loop() {
  int cnt = 0;
  long pc_bat = 0;
  int car_bat = 17;
  long volt_pc = 0;
  float volt_pc_disp = 0; //測定する電圧値
  float pc_per = 0 ;
  static float prev_val = 0;
  volt_pc = measure(); //電圧測定
  pc_disp(volt_pc);
  volt_pc_disp = (volt_pc + 500) / 1000; //測定値をわかりやすく変換
  pc_bat = volt_pc_disp - Min_V;   //残量＝測った電圧値ー最低駆動電圧
  pc_per = (float)pc_bat / 77; //目盛りをそれっぽく合わせた気がする

  //値が測定値より小さくなったらlcdの表示を一度クリア
  if (pc_per >= 0) {
    if (prev_val > pc_per) {
      lcd.clear();
    }

    //台車の方
    per_disp(pc_per);
    for (cnt = 0; cnt < (int)pc_per / 10; cnt++) {
      disp(cnt, 2);
      disp(cnt, 3);
    }
  }
  /*for(cnt=0;cnt<pc_bat;cnt++){
    disp(cnt,1);
    }*/
  /* wagon_disp();
    for(cnt=0;cnt<car_bat;cnt++){
      disp(cnt,3);
    }*/
  Serial.println("cocoa");
  //Serial.println((volt_pc + (1000/2)) / 1000);
  Serial.println(pc_per);
  //Serial.println(pc_per);
  delay(100);
  prev_val = pc_per;
}
