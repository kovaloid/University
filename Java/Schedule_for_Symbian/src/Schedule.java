import javax.microedition.lcdui.*;
import java.util.Calendar;
import java.util.Date;
import javax.microedition.rms.*;
import java.io.*;

public class Schedule implements CommandListener {
	
	private static final int MODE_ACTUAL=0; // Сегодня, Завтра, Все
	private static final int MODE_DOW=1;    // День недели
	private static final int MODE_NUMWEEK=2;     // Числитель / Знаменатель
	private static final int MODE_RES=3; //Режим показа пары
	private static final int MODE_DETAILS=4;
	private static final int MODE_INPUT=5; //Ввод пары
	private static final int MODE_PARAM=6; //Ввод параметров

	private static final int SCHEDULE_TODAY=0; //Выбор в главном меню
	private static final int SCHEDULE_TOMORROW=1;
	private static final int SCHEDULE_DOW=2;
	private static final int SCHEDULE_INPUT=3;
	private static final int SCHEDULE_PARAM=4;
	private static final int SCHEDULE_ABOUT=5; //Помощь

	private static final int WEEK_CHIS=0;
	private static final int WEEK_ZNAM=1;
	private static boolean changed=false;//были изменения?

	private int mode=0; //Режим экрана
	private int scheduleMode=0; //Режим расписания
	private int dow=0; //День недели - выбранный, 0=Пн,...,5=Сб
	private int cz=0;  // Числитель/Знаменатель
	private boolean firstDOW=true, firstCZ=true; //Первый вход в списки?

	private int empLastCount=0; // Количество пустых пар в конце - удаляем лишние

	private Command cmdExit = new Command("Выход", Command.EXIT, 3);
	public Command cmdBack = new Command("Назад", Command.BACK, 1);
	private Command cmdExitFirst = new Command("Выход", Command.EXIT, 1);
	private Command cmdGo = new Command("Сохранить", Command.ITEM, 1);
	private Command cmdChange = new Command("Изменить", Command.ITEM, 2);
	private Command cmdDelete = new Command("Удалить", Command.ITEM, 3);
	private Command cmdDeleteAll = new Command("Удалить все", Command.ITEM, 4);
	private Command confirmOK = new Command ("OK",Command.OK, 2);
	private Command confirmCancel = new Command ("Отмена",Command.CANCEL, 1);

	private int OCH_MONTH = 8; // Отсчет числителя от этого месяца (1-february)
	private int OCH_DAY = 1; // Отсчет числителя от этого дня
	private int TIME_SDVIG = 0; //Сдвиг системного времени

	private RecordStore rs=null;  
	private midlet midlet;

	private final int PAIRS=6;  //количество пар
 // Название пары 1 недели, аудитория, название пары 2 недели, аудитория
 // Первый символ аудитории * - лекция ! - практика # - лабораторная
	private String [][][] schedule =  {  // [день недели][номер пары][]
	 {
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}
	 },
	 {
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}
	 },
	 {
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}
	 },
	 {
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}
	 },
	 {
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}
	 },
	 {
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}, 
	  {"                ", "      ", "                ", "      "}
	 }
	};

	private static final int[][] call=  {  //время начала и конца пар
	 {8, 0, 9, 45}, 
	 {10, 0, 11, 45}, 
	 {12, 0, 12, 45}, 
	 {14, 0, 15, 45},
	 {16, 0, 17, 45}, 
	 {18, 0, 19, 45}
	};

	private static String [] actualStr =  { "Сегодня", "Завтра", "День недели", "Ввод пары", "Настройки", "Помощь" };

	private static String [] dowStr =  { "Понедельник",  "Вторник", "Среда", "Четверг", "Пятница",  "Суббота" };

	private static String [] shortDays =  { "Вс", "Пн", "Вт", "Ср", "Чт", "Пт", "Сб" };

	private static String [] monthStr = { "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь" };
    
	private static String [] czStr =  { "1 неделя", "2 неделя" };
 
	private static String [] typeStr =  { "Лекция", "Практика", "Лабораторная" };
	private static String [] labelStr =  { "*","!","#" };

	private String [] actualMenuStr = { "go1", "go2", "go3", "schedule", "settings", "help" };
  
	private final int[] mda = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
 
	public int hour,min,month,day,dayOfWeek,year,numWeek;
    
	private List lstActual;  //список главного меню
	private List lstDOW;  //список дней недели
	private List lstCZ;  //список числитель\знаменатель
	private List lstRes = new List("Расписание", Choice.IMPLICIT);  //список предметов конкретный день
  
	private Form frmRes = new Form("Подробности");
	private StringItem[] strRes;
	private StringItem label = new StringItem("По расписанию: ","");
   
	private Form frmInput=new Form ("Ввод пары");
	private TextField numberInput = new TextField ("Номер пары", null, 1, TextField.NUMERIC);
	private TextField nameInput = new TextField ("Название", null, 16, TextField.ANY);
	private TextField audInput = new TextField ("Аудитория", null, 6, TextField.ANY);
	private Image [] weekDays={null,null,null,null,null,null}; //иконки дней недели
	private Image [] weekNums={null,null};  //иконки числитель\знаменатель
	private Image [] zTypes={null,null,null};  //иконки типов занятий
	private Image currIm=null;  //иконка текущего занятия
	private Image [] pairNums={null,null,null,null,null,null};  //иконки "окон" в расписании
	private Image [] actualMenu={null,null,null,null,null,null};  //иконки главного меню
	private ChoiceGroup weekDayInput=null;  //блок выбора дня недели
	private ChoiceGroup weekInput=null;  //блок выбора числителя знаменателя
	private ChoiceGroup typeInput=null;  //блок выбора типа занятия
 
	private Form frmParam=new Form ("Настройки");
	private DateField[] startPair;
	private DateField[] endPair; 
	private Form frmAlert=new Form ("Внимание!");
	private StringItem txtAlert=new StringItem ("", "Внимание! Вы действительно хотите удалить все записи?");
 
	private TextField day1Input = new TextField ("День 1 недели", OCH_DAY+"", 2, TextField.NUMERIC);  
	private ChoiceGroup month1Input = new ChoiceGroup ("Месяц 1 недели", ChoiceGroup.EXCLUSIVE, monthStr, null);
	private TextField time1Input = new TextField ("Сдвиг системного времени", TIME_SDVIG+"", 3, TextField.NUMERIC);
    
	private Display display;

//смещает индекс для работы со списком
	public int selectDayIndex (int d) {
		if (d==0) return (0);  
		else return (d-1);
	}
 
//обновление времени и заголовков, где содержится информация о времени
	public void updateListHeaders () {
		Calendar cal = Calendar.getInstance();
		if (TIME_SDVIG!=0) { 
			long newTime = cal.getTime().getTime()+TIME_SDVIG*3600000;
			cal.setTime (new Date (newTime));
		}
		hour = cal.get(Calendar.HOUR_OF_DAY);
		min  = cal.get(Calendar.MINUTE);
		month  = cal.get(Calendar.MONTH);
		day  = cal.get(Calendar.DAY_OF_MONTH);
		dayOfWeek = cal.get(Calendar.DAY_OF_WEEK)-1; //т.к. вернет 1 = Вс
		year = cal.get(Calendar.YEAR);
		cz=getCZ (year,month,day);
		String weeknow=""+numWeek+"["+(cz+1)+"]";
		String weekday=shortDays[dayOfWeek];
		String now=""+oNum(day)+"."+oNum(month+1)+"."+oNum(year%100)+","+weekday+","+weeknow+"н.";
		lstActual.setTitle(now);
		lstDOW.setTitle("День недели ["+weekday+"]");
		lstCZ.setTitle("Неделя "+weeknow);
	} 

//конструктор класса, в котором формируется меню и читаются данные
	public Schedule(midlet midlet)  { 
		this.midlet=midlet;
		int i;
		try {
			for (i=1;i<7;i++)
				weekDays[i-1] = Image.createImage("/"+i+".png");
			for (i=1;i<3;i++)
				weekNums[i-1]=Image.createImage("/w"+i+".png");
			for (i=1;i<4;i++)
				zTypes[i-1]=Image.createImage("/z"+i+".png");
			currIm = Image.createImage("/z4.png");
			for (i=0; i<6; i++)
				actualMenu[i]=Image.createImage("/"+actualMenuStr[i]+".png");
			for (i=1;i<7;i++)
				pairNums[i-1] = Image.createImage("/l"+i+".png");
		}
		catch (java.io.IOException e) { errorMsg (e.getMessage()); }

		lstActual = new List("Расписание", Choice.IMPLICIT, actualStr, actualMenu);
		lstDOW = new List("День недели", Choice.IMPLICIT, dowStr, weekDays);
		lstCZ = new List("Неделя", Choice.IMPLICIT, czStr, weekNums);

		lstActual.addCommand(cmdExitFirst);
		lstActual.setCommandListener(this);

		weekDayInput = new ChoiceGroup ("День недели", ChoiceGroup.EXCLUSIVE, dowStr, weekDays);
		weekInput = new ChoiceGroup ("Номер недели", ChoiceGroup.MULTIPLE, czStr, weekNums);
		typeInput = new ChoiceGroup ("Тип занятия", ChoiceGroup.EXCLUSIVE, typeStr, zTypes);

		mode = MODE_ACTUAL;
		display = Display.getDisplay(midlet);
		display.setCurrent(lstActual);
		readRecords ();
		initForms ();
	}

//инициализация меню и подменю
	public void initForms () {  
		updateListHeaders();   
		strRes = new StringItem[5]; 
		for (int i=0; i<5; i++) {
			strRes[i] = new StringItem(null, null);
		}
		strRes[0].setLabel("Предмет: ");
		strRes[1].setLabel("Аудитория: ");
		strRes[2].setLabel("Начало: ");
		strRes[3].setLabel("Окончание: ");
		strRes[4].setLabel("Тип занятия: ");

		lstDOW.addCommand(cmdBack);
		lstDOW.setCommandListener(this);

		lstCZ.addCommand(cmdBack);
		lstCZ.setCommandListener(this);

		lstRes.addCommand(cmdBack);
		lstRes.setCommandListener(this);
  
		frmRes.addCommand(cmdBack);
		frmRes.addCommand(cmdChange);
		frmRes.addCommand(cmdExit);
		frmRes.addCommand(cmdDelete);
		frmRes.addCommand(cmdDeleteAll);
		frmRes.setCommandListener(this);
  
		frmInput.append (numberInput);
		frmInput.append (nameInput);
		frmInput.append (audInput);
		frmInput.append (weekDayInput);
		frmInput.append (weekInput);
		frmInput.append (typeInput);
		frmInput.addCommand(cmdBack);
		frmInput.addCommand(cmdGo);      
		frmInput.setCommandListener(this);
  
		frmParam.append (day1Input); 
		day1Input.setString(OCH_DAY+"");
		frmParam.append (month1Input); 
		month1Input.setSelectedIndex(OCH_MONTH,true);
		frmParam.append (time1Input); 
		time1Input.setString(TIME_SDVIG+"");
  
		frmAlert.append (txtAlert);
		frmAlert.addCommand(confirmOK);
		frmAlert.addCommand(confirmCancel);
		frmAlert.setCommandListener (this);
  
		startPair = new DateField[PAIRS];
		endPair = new DateField[PAIRS]; 
		Calendar cal=Calendar.getInstance();
		Date dt=new Date(0);
		cal.setTime(dt);
		for (int i=0; i<PAIRS; i++) {
			startPair[i]=new DateField ("Начало "+(i+1)+" пары",DateField.TIME);
			endPair[i]=new DateField ("Конец "+(i+1)+" пары", DateField.TIME);
			cal.set (Calendar.DAY_OF_MONTH,1);
			cal.set (Calendar.MONTH,Calendar.JANUARY);
			cal.set (Calendar.YEAR,1970);
			cal.set (Calendar.SECOND,0);
			cal.set (Calendar.MILLISECOND,0);
			cal.set (Calendar.HOUR_OF_DAY,call[i][0]);
			cal.set (Calendar.MINUTE,call[i][1]);
			dt=cal.getTime();
			startPair[i].setDate(dt);
			frmParam.append (startPair[i]);
			cal.set(Calendar.HOUR_OF_DAY,call[i][2]);
			cal.set(Calendar.MINUTE,call[i][3]);
			dt=cal.getTime();
			endPair[i].setDate(dt);
			frmParam.append (endPair[i]);
		}
		frmParam.addCommand(cmdBack);
		frmParam.addCommand(cmdGo);      
		frmParam.setCommandListener(this);
	}

//чтение данных при открытии приложения
	public void readRecords () {
		try {
			rs = RecordStore.openRecordStore ("mydata", true);
		}
		catch (RecordStoreFullException e) { // no room left for more data
			errorMsg("Нет места для сохранения данных");
			rs=null; return;
		}
		catch (RecordStoreNotOpenException e) { // store has been closed
			errorMsg("Не могу открыть данные");   
			rs=null; return;
		}
		catch (RecordStoreException e) { // general error
			errorMsg("Ошибка работы с данными");
			rs=null; return;
		} 
		if (rs!=null) {
			try {
				byte[] arrData = rs.getRecord(1);
				ByteArrayInputStream bytes = new ByteArrayInputStream(arrData, 0, 3820);
				DataInputStream dis = new DataInputStream(bytes);
				int n=0;
				for (int i=0; i<6; i++)
					for (int j=0; j<PAIRS; j++)
						for (int k=0; k<4; k++) {
							if ((k==0) || (k==2)) n=16; else n=6;
							schedule[i][j][k]=dis.readUTF();
							if (schedule[i][j][k].length() < n) {
								dis.skip (n-schedule[i][j][k].length());
							}
						}
				for (int i=0; i<PAIRS; i++)
					for (int j=0; j<4; j++) {
						call[i][j]=dis.readInt();   
					}
				OCH_MONTH = dis.readInt();
				OCH_DAY = dis.readInt();
				TIME_SDVIG = dis.readInt();
			}
			catch (IOException ioe) {
				//errorMsg("Ошибка ввода/вывода на чтении данных");
			}        
			catch (RecordStoreException ex) {
				//errorMsg("Ошибка чтения данных");
			}
		}
		else {
			errorMsg("Ошибка - RecordStore пуст");
		}   
	}
 
//сохранение данных перед выходом
	void saveRecords () {
		if (rs!=null) {
			ByteArrayOutputStream bytes = new ByteArrayOutputStream();
			DataOutputStream dos = new DataOutputStream(bytes);
			try {   
				int n=0;  
				for (int i=0; i<6; i++)
					for (int j=0; j<PAIRS; j++)
						for (int k=0; k<4; k++) {
							if ((k==0) || (k==2)) n=16; else n=6;
							dos.writeUTF(schedule[i][j][k]);
							if (schedule[i][j][k].length() < n) {
								for (int l=schedule[i][j][k].length(); l<n; l++) dos.writeByte (0);
							}
						}
    
				for (int i=0; i<PAIRS; i++)
					for (int j=0; j<4; j++) {
						dos.writeInt(call[i][j]);  
					}
				dos.writeInt(OCH_MONTH);
				dos.writeInt(OCH_DAY);
				dos.writeInt(TIME_SDVIG);
				rs.setRecord(1, bytes.toByteArray(), 0, bytes.toByteArray().length);
			}
			catch (IOException ioe) {
				errorMsg("Ошибка записи данных в поток");
			}         
			catch (InvalidRecordIDException ridex) {
				try {
					rs.addRecord(bytes.toByteArray(), 0, bytes.toByteArray().length);            
				}              
				catch (RecordStoreException ex) {
					errorMsg("Не могу добавить запись");
				}
			} 
			catch (RecordStoreException ex) {
				errorMsg("Не могу сохранить данные");
			}
		} 
		try {
			rs.closeRecordStore();      
			rs=null;
		}
		catch (RecordStoreException ex) {}
	} 

//проверка на високосный год
	boolean leapyear (int year) {
		if ( (year%4==0) && (year%100!=0) || (year%400==0) ) {
			mda[1]= 29; return true;
		} 
		else { mda[1]=28; return false; }
	}

//проверка правильности ввода даты в меню "Ввод пары"
	boolean correctDate (int year, int d,int m) {
		leapyear (year);
		if ((d<1) || (d>mda[m]) || (m<0) || (m>11)) return false;
		return true;
	}    

//возвращает номер дня недели по известному дню, месяцу и году
	int getWeekDay (int year, int month, int day) {
		Calendar c1 = Calendar.getInstance();
		c1.set(Calendar.YEAR,year);
		c1.set(Calendar.MONTH,month);
		c1.set(Calendar.DAY_OF_MONTH,day);
		int dayOfWeek = c1.get(Calendar.DAY_OF_WEEK)-1; //вернет 1 = Вс
		if (dayOfWeek==0) dayOfWeek=7; //1=Пн,...,7=Вс
		return dayOfWeek;
	}
  
//возвращает числитель или знаменатель
	int getCZ (int year, int month, int day) {
		int m=OCH_MONTH;
		int d=OCH_DAY;
		int w=1;
		if ((m==month) && (d==day)) { numWeek=w; return WEEK_CHIS; }
		if ( (m>month) || (m==month) && (d>day) ) year--;
		leapyear (year);
		int wd=getWeekDay (year,m,d);
		if (wd!=1) { //неполная 1 неделя возможна
			do {
				d++;
				if ((m==month) && (d==day)) { numWeek=w; return WEEK_CHIS; }
				if (d>mda[m]) {
					d=1; m++;
					if (m>11) { m=0; year++; leapyear (year); }
				}
				wd++;
				if (wd>7) { wd=1; break; }
			} while (true);
			w=2;
		}
		do {
			if ( (m==month) && (d==day) ) break;
			d++;
			if (d>mda[m]) {
				d=1; m++;
				if (m>11) { m=0; year++; leapyear (year); }
			}
			wd++;
			if (wd>7) { 
				wd=1; w++; 
			}
		} while (true); 
		numWeek=w; //сохранили глобальный номер недели
		if (w%2==0) return WEEK_ZNAM; 
		else return WEEK_CHIS;
	}

//проверка на пустоту строки
	boolean isVoidString (String s) {
		if (s.trim().length()<1) return true;
		return false;
	}

//ставит пару в списке и рядом с ней соответствующую иконку (лекция, лаба, практика или окно)
	void addRes(int day, int i, int c, int hour, int min) {
		Image img = null; // Подбор картинки
		if (isVoidString (schedule[day][i][c+1])==false) {
			if (schedule[day][i][c+1].startsWith("*")) img = zTypes[0]; 
			else if (schedule[day][i][c+1].startsWith("!")) img = zTypes[1]; 
			else if (schedule[day][i][c+1].startsWith("#")) img = zTypes[2];
		}
		if (isVoidString (schedule[day][i][c])==false) { // Непустая пара
			if ((scheduleMode==SCHEDULE_TODAY) && (actual(i+1, hour, min)))
				lstRes.append((i+1)+". "+schedule[day][i][c], currIm); 
			else 
				lstRes.append((i+1)+". "+schedule[day][i][c], img);
			empLastCount = 0;
		} 
		else {
			if ((scheduleMode==SCHEDULE_TODAY)&&(actual(i+1, hour, min))) 
				lstRes.append((i+1)+". ---", currIm); 
			else lstRes.append((i+1)+". ---", pairNums[i]);
			empLastCount++;
		}
	}

//формирует список предметов в конкретный день
	void prepairRes (int hour, int min) {
		while (lstRes.size()>0) lstRes.delete(0);
		empLastCount=0;
		for (int i=0; i<schedule[dow].length; i++) { // Сколько пар в dayOfWeek
			addRes(dow, i, 2*cz, hour, min);
		}
		while (empLastCount-->0) lstRes.delete(lstRes.size()-1);
		mode = MODE_RES;
		lstRes.setTitle ("Расписание ["+shortDays[dow+1]+","+(cz+1)+"н.]");
		display.setCurrent(lstRes);
	}

//проверяет проходит ли в данный момент пара по расписанию
	boolean actual(int n, int hour, int min) {
		if (n==1) { // Первая пара
			if ((hour*60+min)<=(call[0][2]*60+call[0][3])) // Первая пара еще не закончилась
				return true; 
			else return false;
		} 
		else if ((n>1) && (n<=PAIRS))  {
			if ( ((hour*60+min) > (call[n-2][2]*60+call[n-2][3]) ) &&
					((call[n-1][2]*60+call[n-1][3]) >= (hour*60+min)))
				return true; 
			else return false;
		} 
		else return false;
	}

//преобразует число в строку
	public String oNum(int value) {
		if (value<10) return new String("0"+value); 
		else return new String(""+value);
	}

//формирует информацию (аудитория, начало, конец и т.д.) о конкретном пункте списка предметов
	private void prepairDetails (int selResInd, int c) {
		String pairName = "",
				aud = "",
				startStr = "",
				endStr = "",
				tStr = "",
				voidStr="---";
		if (isVoidString (schedule[dow][selResInd][c])==false) pairName = schedule[dow][selResInd][c]; 
		else pairName = voidStr;
		strRes[0].setText(pairName);
		frmRes.append(strRes[0]);
		if (isVoidString (schedule[dow][selResInd][c+1])==false) {
			aud = schedule[dow][selResInd][c+1].substring(1);
			tStr=schedule[dow][selResInd][c+1].substring(0,1);
			if (tStr.equals("*")) strRes[4].setText(typeStr[0]);
			else if (tStr.equals("!")) strRes[4].setText(typeStr[1]);
			else strRes[4].setText(typeStr[2]);
		}
		else {
			aud = voidStr;
			strRes[4].setText(voidStr);
		}
		strRes[1].setText(aud);
		frmRes.append(strRes[1]);
		startStr = call[selResInd][0]+":"+oNum(call[selResInd][1]);
		endStr = call[selResInd][2]+":"+oNum(call[selResInd][3]);
		strRes[2].setText(startStr);
		frmRes.append(strRes[2]);
		strRes[3].setText(endStr);
		frmRes.append(strRes[3]);
		frmRes.append(strRes[4]);
		frmRes.append (label);
		label.setText (shortDays[dow+1]+", "+ (c==0? "1" : "2")+" нед., "+(selResInd+1) +" пара");
		mode = MODE_DETAILS;
		display.setCurrent(frmRes);
	}

//проверка корректности введенных настроек
	boolean correctParam () {
		Calendar cal=Calendar.getInstance(); 
		Date d1=new Date(0); 
		cal.setTime(d1);
		int i,h1,m1,h2,m2,pred=0;
		for (i=0; i<PAIRS; i++) {
			d1=startPair[i].getDate();
			cal.setTime (d1);
			h1=cal.get (Calendar.HOUR_OF_DAY);
			m1=cal.get (Calendar.MINUTE);
			d1=endPair[i].getDate();
			cal.setTime (d1);
			h2=cal.get (Calendar.HOUR_OF_DAY);
			m2=cal.get (Calendar.MINUTE);
			if (h1*60+m1 >= h2*60+m2) {
				errorMsg("Ошибка! Начало "+(i+1)+" пары позже конца: "+oNum(h1)+":"+oNum(m1)+"-"+oNum(h2)+":"+oNum(m2));
				return false;
			}
			if (i>0) {
				if (h1*60+m1 <= pred) {
					int h0 = pred/60;
					int m0 = pred - h0*60;
					errorMsg("Ошибка! Начало "+(i+1)+" пары раньше конца "+i+": "+oNum(h0)+":"+oNum(m0)+"-"+oNum(h1)+":"+oNum(m1));
					return false;           
				}    
			}
			pred=h2*60+m2;
			call[i][0]=h1;
			call[i][1]=m1;
			call[i][2]=h2;
			call[i][3]=m2;
		}
		if (day1Input.getString().trim().length()<1) {
			errorMsg("День начала не м.б. пустым!");
			return false;
		}
		int d=Integer.parseInt(day1Input.getString().trim());
		int m=month1Input.getSelectedIndex();
		if (correctDate (year,d,m)==false) {
			//errorMsg(""+oNum(d)+"."+oNum(m+1)+" некорректно в "+year);
			errorMsg("Некорректный день в данном месяце ("+oNum(m+1)+"."+year+")");
			return false;
		}    
		if (time1Input.getString().trim().length()<1) {
			errorMsg("Поле \"Сдвиг времени\" не может быть пустым!");
			return false;
		}
		int t=Integer.parseInt(time1Input.getString().trim());
		if ((t<-12) || (t>12)) {
			errorMsg("Допустимы значения сдвига времени от -12 до 12 включительно!");
			return false;
		}
		OCH_MONTH = m;
		OCH_DAY = d;
		TIME_SDVIG = t;
		return true;
	}     
 
//проверка корректности введенных пар
	boolean correctInput () {
		if (numberInput.getString().trim().length()<1) {
			errorMsg("Номер пары не м.б. пустым!");
			return false;
		}
		int n=Integer.parseInt(numberInput.getString());
		if ((n<1) || (n>PAIRS)) {
			errorMsg("Номер пары д.б. от 1 до "+ PAIRS+ "!");
			return false;
		}
		String name=nameInput.getString().trim();
		if (name.length()<1) {
			errorMsg("Название пары не м.б. пустым!");
			return false;
		}
		String aud=audInput.getString().trim();
		if (aud.length()<1) {
			errorMsg("Аудитория не м.б. пустой!");
			return false;
		}
		int numday=weekDayInput.getSelectedIndex();
		boolean w1=weekInput.isSelected(0);
		boolean w2=weekInput.isSelected(1);
		if ((w1==false) && (w2==false)) {
			errorMsg("Выберите 1 и/или 2 нед.!");
			return false;
		}
		int type=typeInput.getSelectedIndex();
		if (w1==true) {
			schedule[numday][n-1][0]=name;
			schedule[numday][n-1][1]=labelStr[type]+aud;
		} 
		if (w2==true) {
			schedule[numday][n-1][2]=name;
			schedule[numday][n-1][3]=labelStr[type]+aud;
		}
		return true;   
	}

//вывод сообщения об ошибке на дисплей экрана
	public void errorMsg (String strError) {
		Alert a = new Alert("Ошибка:", strError, null, AlertType.ERROR);
		a.setTimeout(3000);
		display.setCurrent(a);  
	}
 
//реакция на нажатие различных клавиш
	public void commandAction(Command c, Displayable d)  {
		if ((c==cmdExitFirst) || (c==cmdExit)) {
			if (changed==true) saveRecords();   
			midlet.exitMIDlet();
		} 
		else if (c==cmdDelete) { //Кнопка Удалить
			int selResInd = lstRes.getSelectedIndex();
			schedule[dow][selResInd][cz*2]="";
			schedule[dow][selResInd][cz*2+1]="";
			mode = MODE_ACTUAL;
			display.setCurrent(lstActual);
			changed = true;
		}
		else if (c==cmdChange) { //Кнопка Изменить
			int selResInd = lstRes.getSelectedIndex();
			nameInput.setString(schedule[dow][selResInd][cz*2].trim());
			audInput.setString(schedule[dow][selResInd][cz*2+1].substring(1).trim());
			weekDayInput.setSelectedIndex(dow,true);
			if (cz==0) {
				weekInput.setSelectedIndex(0,true);
				weekInput.setSelectedIndex(1,false);
			}
			else {
				weekInput.setSelectedIndex(0,false);
				weekInput.setSelectedIndex(1,true);   
			}    
			char c1=schedule[dow][selResInd][cz*2+1].charAt(0);
			int k=0;
			for (int i=0; i<3; i++) if (c1==labelStr[i].charAt(0)) { k=i; break; }
			typeInput.setSelectedIndex(k,true);
			numberInput.setString((selResInd+1)+"");
			mode=MODE_INPUT;
			display.setCurrent(frmInput);
		}    
		else if (c==cmdDeleteAll) { //Кнопка Удалить все
			display.setCurrent(frmAlert);
		}
		else if (c==confirmOK) { //Подтвердить изменения
			for (int i=0; i<6; i++)
				for (int j=0; j<PAIRS; j++)
					for (int k=0; k<4; k++) schedule[i][j][k]="";
			mode = MODE_ACTUAL;
			display.setCurrent(lstActual);
			changed = true;
		}
		else if (c==confirmCancel) { //Отменить изменения
			mode = MODE_ACTUAL;
			display.setCurrent(lstActual);
		}    
		else if (c==cmdBack) { //Кнопка Назад
			if (mode!=MODE_DETAILS) updateListHeaders();
			switch (mode) {
			case (MODE_DOW):
			case (MODE_INPUT):
			case (MODE_PARAM):
				mode = MODE_ACTUAL;
			display.setCurrent(lstActual);
			break;
			case (MODE_NUMWEEK):
				mode = MODE_DOW;
			if (firstDOW==true) {
				lstDOW.setSelectedIndex(selectDayIndex(dayOfWeek),true);
				firstDOW=false;
			} 
			display.setCurrent(lstDOW);
			break;
			case (MODE_RES):
				switch (scheduleMode) {
				case (SCHEDULE_DOW):
					mode = MODE_NUMWEEK;
				if (firstCZ==true) {
					lstCZ.setSelectedIndex (cz,true);
					firstCZ=false;
				} 
				display.setCurrent(lstCZ);
				break;
				default:
					mode = MODE_ACTUAL;
					display.setCurrent(lstActual);
					break;
				}
			break;
			case (MODE_DETAILS):
				mode = MODE_RES;
			display.setCurrent(lstRes);
			break;
			}
		} 
		else if (c==List.SELECT_COMMAND) { //Выбор из главного списка
			switch (mode) {
			case MODE_ACTUAL:
				scheduleMode = lstActual.getSelectedIndex();
				switch (scheduleMode) {
				case SCHEDULE_TODAY:
					updateListHeaders();   
					dow = dayOfWeek-1; // 0 = Вс
					if (dow!=-1) prepairRes (hour, min);
					break;
				case SCHEDULE_TOMORROW:
					updateListHeaders();   
					dow = dayOfWeek;
					if (dow==0) {
						if (cz==WEEK_CHIS) cz=WEEK_ZNAM; else cz=WEEK_CHIS;
					}    
					if (dow!=6) prepairRes (hour, min);
					break;
				case SCHEDULE_DOW:
					mode = MODE_DOW;
					if (firstDOW==true) {
						lstDOW.setSelectedIndex(selectDayIndex(dayOfWeek),true);
						firstDOW=false;
					} 
					display.setCurrent(lstDOW);
					break;
				case SCHEDULE_INPUT:
					mode = MODE_INPUT;
					display.setCurrent(frmInput);
					break;
				case SCHEDULE_PARAM:
					mode = MODE_PARAM;
					display.setCurrent(frmParam);
					break;
				case SCHEDULE_ABOUT:
					new Message (midlet, lstActual, "Помощь").show ("Расписание занятий\nv.1.0 (RU)\n\n"
							+ "Введите день и месяц начала занятий в меню \"Настройки\". "
							+ "Там же выберите время начала пар. Пункт \"Ввод пары\" позволяет добавить занятие. "
							+ "Остальные функции доступны с экрана \"Подробности\" (по выбору пары из списка).\n\n"
							+ "(C) Koval (kov3000@ya.ru)"); 
					break;
				}
				break;
			case MODE_DOW:
				dow = lstDOW.getSelectedIndex(); //0 = Пн
				mode = MODE_NUMWEEK;
				if (firstCZ==true) {
					lstCZ.setSelectedIndex (cz,true);
					firstCZ=false;
				} 
				display.setCurrent(lstCZ);
				break;
			case MODE_NUMWEEK:
				cz = lstCZ.getSelectedIndex();
				prepairRes (hour, min);
				break;
			case (MODE_RES): // Вывод данных по конкретной паре
				while (frmRes.size()>0) frmRes.delete(0);
			int selResInd = lstRes.getSelectedIndex();
			prepairDetails (selResInd, 2*cz);
			break;
			}
		}
		else if (c==cmdGo) {
			switch (mode) {
			case MODE_INPUT:
				if (correctInput()==true) {
					changed=true;
					updateListHeaders();   
					mode = MODE_ACTUAL;
					display.setCurrent(lstActual);   
				}
				break;
			case MODE_PARAM:
				if (correctParam()==true) {
					changed=true;
					updateListHeaders();   
					mode = MODE_ACTUAL;
					display.setCurrent(lstActual);            
				}
				break;
			} 
		}
	}
   
}

