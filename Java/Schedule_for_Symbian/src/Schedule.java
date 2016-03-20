import javax.microedition.lcdui.*;
import java.util.Calendar;
import java.util.Date;
import javax.microedition.rms.*;
import java.io.*;

public class Schedule implements CommandListener {
	
	private static final int MODE_ACTUAL=0; // �������, ������, ���
	private static final int MODE_DOW=1;    // ���� ������
	private static final int MODE_NUMWEEK=2;     // ��������� / �����������
	private static final int MODE_RES=3; //����� ������ ����
	private static final int MODE_DETAILS=4;
	private static final int MODE_INPUT=5; //���� ����
	private static final int MODE_PARAM=6; //���� ����������

	private static final int SCHEDULE_TODAY=0; //����� � ������� ����
	private static final int SCHEDULE_TOMORROW=1;
	private static final int SCHEDULE_DOW=2;
	private static final int SCHEDULE_INPUT=3;
	private static final int SCHEDULE_PARAM=4;
	private static final int SCHEDULE_ABOUT=5; //������

	private static final int WEEK_CHIS=0;
	private static final int WEEK_ZNAM=1;
	private static boolean changed=false;//���� ���������?

	private int mode=0; //����� ������
	private int scheduleMode=0; //����� ����������
	private int dow=0; //���� ������ - ���������, 0=��,...,5=��
	private int cz=0;  // ���������/�����������
	private boolean firstDOW=true, firstCZ=true; //������ ���� � ������?

	private int empLastCount=0; // ���������� ������ ��� � ����� - ������� ������

	private Command cmdExit = new Command("�����", Command.EXIT, 3);
	public Command cmdBack = new Command("�����", Command.BACK, 1);
	private Command cmdExitFirst = new Command("�����", Command.EXIT, 1);
	private Command cmdGo = new Command("���������", Command.ITEM, 1);
	private Command cmdChange = new Command("��������", Command.ITEM, 2);
	private Command cmdDelete = new Command("�������", Command.ITEM, 3);
	private Command cmdDeleteAll = new Command("������� ���", Command.ITEM, 4);
	private Command confirmOK = new Command ("OK",Command.OK, 2);
	private Command confirmCancel = new Command ("������",Command.CANCEL, 1);

	private int OCH_MONTH = 8; // ������ ��������� �� ����� ������ (1-february)
	private int OCH_DAY = 1; // ������ ��������� �� ����� ���
	private int TIME_SDVIG = 0; //����� ���������� �������

	private RecordStore rs=null;  
	private midlet midlet;

	private final int PAIRS=6;  //���������� ���
 // �������� ���� 1 ������, ���������, �������� ���� 2 ������, ���������
 // ������ ������ ��������� * - ������ ! - �������� # - ������������
	private String [][][] schedule =  {  // [���� ������][����� ����][]
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

	private static final int[][] call=  {  //����� ������ � ����� ���
	 {8, 0, 9, 45}, 
	 {10, 0, 11, 45}, 
	 {12, 0, 12, 45}, 
	 {14, 0, 15, 45},
	 {16, 0, 17, 45}, 
	 {18, 0, 19, 45}
	};

	private static String [] actualStr =  { "�������", "������", "���� ������", "���� ����", "���������", "������" };

	private static String [] dowStr =  { "�����������",  "�������", "�����", "�������", "�������",  "�������" };

	private static String [] shortDays =  { "��", "��", "��", "��", "��", "��", "��" };

	private static String [] monthStr = { "������", "�������", "����", "������", "���", "����", "����", "������", "��������", "�������", "������", "�������" };
    
	private static String [] czStr =  { "1 ������", "2 ������" };
 
	private static String [] typeStr =  { "������", "��������", "������������" };
	private static String [] labelStr =  { "*","!","#" };

	private String [] actualMenuStr = { "go1", "go2", "go3", "schedule", "settings", "help" };
  
	private final int[] mda = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
 
	public int hour,min,month,day,dayOfWeek,year,numWeek;
    
	private List lstActual;  //������ �������� ����
	private List lstDOW;  //������ ���� ������
	private List lstCZ;  //������ ���������\�����������
	private List lstRes = new List("����������", Choice.IMPLICIT);  //������ ��������� ���������� ����
  
	private Form frmRes = new Form("�����������");
	private StringItem[] strRes;
	private StringItem label = new StringItem("�� ����������: ","");
   
	private Form frmInput=new Form ("���� ����");
	private TextField numberInput = new TextField ("����� ����", null, 1, TextField.NUMERIC);
	private TextField nameInput = new TextField ("��������", null, 16, TextField.ANY);
	private TextField audInput = new TextField ("���������", null, 6, TextField.ANY);
	private Image [] weekDays={null,null,null,null,null,null}; //������ ���� ������
	private Image [] weekNums={null,null};  //������ ���������\�����������
	private Image [] zTypes={null,null,null};  //������ ����� �������
	private Image currIm=null;  //������ �������� �������
	private Image [] pairNums={null,null,null,null,null,null};  //������ "����" � ����������
	private Image [] actualMenu={null,null,null,null,null,null};  //������ �������� ����
	private ChoiceGroup weekDayInput=null;  //���� ������ ��� ������
	private ChoiceGroup weekInput=null;  //���� ������ ��������� �����������
	private ChoiceGroup typeInput=null;  //���� ������ ���� �������
 
	private Form frmParam=new Form ("���������");
	private DateField[] startPair;
	private DateField[] endPair; 
	private Form frmAlert=new Form ("��������!");
	private StringItem txtAlert=new StringItem ("", "��������! �� ������������� ������ ������� ��� ������?");
 
	private TextField day1Input = new TextField ("���� 1 ������", OCH_DAY+"", 2, TextField.NUMERIC);  
	private ChoiceGroup month1Input = new ChoiceGroup ("����� 1 ������", ChoiceGroup.EXCLUSIVE, monthStr, null);
	private TextField time1Input = new TextField ("����� ���������� �������", TIME_SDVIG+"", 3, TextField.NUMERIC);
    
	private Display display;

//������� ������ ��� ������ �� �������
	public int selectDayIndex (int d) {
		if (d==0) return (0);  
		else return (d-1);
	}
 
//���������� ������� � ����������, ��� ���������� ���������� � �������
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
		dayOfWeek = cal.get(Calendar.DAY_OF_WEEK)-1; //�.�. ������ 1 = ��
		year = cal.get(Calendar.YEAR);
		cz=getCZ (year,month,day);
		String weeknow=""+numWeek+"["+(cz+1)+"]";
		String weekday=shortDays[dayOfWeek];
		String now=""+oNum(day)+"."+oNum(month+1)+"."+oNum(year%100)+","+weekday+","+weeknow+"�.";
		lstActual.setTitle(now);
		lstDOW.setTitle("���� ������ ["+weekday+"]");
		lstCZ.setTitle("������ "+weeknow);
	} 

//����������� ������, � ������� ����������� ���� � �������� ������
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

		lstActual = new List("����������", Choice.IMPLICIT, actualStr, actualMenu);
		lstDOW = new List("���� ������", Choice.IMPLICIT, dowStr, weekDays);
		lstCZ = new List("������", Choice.IMPLICIT, czStr, weekNums);

		lstActual.addCommand(cmdExitFirst);
		lstActual.setCommandListener(this);

		weekDayInput = new ChoiceGroup ("���� ������", ChoiceGroup.EXCLUSIVE, dowStr, weekDays);
		weekInput = new ChoiceGroup ("����� ������", ChoiceGroup.MULTIPLE, czStr, weekNums);
		typeInput = new ChoiceGroup ("��� �������", ChoiceGroup.EXCLUSIVE, typeStr, zTypes);

		mode = MODE_ACTUAL;
		display = Display.getDisplay(midlet);
		display.setCurrent(lstActual);
		readRecords ();
		initForms ();
	}

//������������� ���� � �������
	public void initForms () {  
		updateListHeaders();   
		strRes = new StringItem[5]; 
		for (int i=0; i<5; i++) {
			strRes[i] = new StringItem(null, null);
		}
		strRes[0].setLabel("�������: ");
		strRes[1].setLabel("���������: ");
		strRes[2].setLabel("������: ");
		strRes[3].setLabel("���������: ");
		strRes[4].setLabel("��� �������: ");

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
			startPair[i]=new DateField ("������ "+(i+1)+" ����",DateField.TIME);
			endPair[i]=new DateField ("����� "+(i+1)+" ����", DateField.TIME);
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

//������ ������ ��� �������� ����������
	public void readRecords () {
		try {
			rs = RecordStore.openRecordStore ("mydata", true);
		}
		catch (RecordStoreFullException e) { // no room left for more data
			errorMsg("��� ����� ��� ���������� ������");
			rs=null; return;
		}
		catch (RecordStoreNotOpenException e) { // store has been closed
			errorMsg("�� ���� ������� ������");   
			rs=null; return;
		}
		catch (RecordStoreException e) { // general error
			errorMsg("������ ������ � �������");
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
				//errorMsg("������ �����/������ �� ������ ������");
			}        
			catch (RecordStoreException ex) {
				//errorMsg("������ ������ ������");
			}
		}
		else {
			errorMsg("������ - RecordStore ����");
		}   
	}
 
//���������� ������ ����� �������
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
				errorMsg("������ ������ ������ � �����");
			}         
			catch (InvalidRecordIDException ridex) {
				try {
					rs.addRecord(bytes.toByteArray(), 0, bytes.toByteArray().length);            
				}              
				catch (RecordStoreException ex) {
					errorMsg("�� ���� �������� ������");
				}
			} 
			catch (RecordStoreException ex) {
				errorMsg("�� ���� ��������� ������");
			}
		} 
		try {
			rs.closeRecordStore();      
			rs=null;
		}
		catch (RecordStoreException ex) {}
	} 

//�������� �� ���������� ���
	boolean leapyear (int year) {
		if ( (year%4==0) && (year%100!=0) || (year%400==0) ) {
			mda[1]= 29; return true;
		} 
		else { mda[1]=28; return false; }
	}

//�������� ������������ ����� ���� � ���� "���� ����"
	boolean correctDate (int year, int d,int m) {
		leapyear (year);
		if ((d<1) || (d>mda[m]) || (m<0) || (m>11)) return false;
		return true;
	}    

//���������� ����� ��� ������ �� ���������� ���, ������ � ����
	int getWeekDay (int year, int month, int day) {
		Calendar c1 = Calendar.getInstance();
		c1.set(Calendar.YEAR,year);
		c1.set(Calendar.MONTH,month);
		c1.set(Calendar.DAY_OF_MONTH,day);
		int dayOfWeek = c1.get(Calendar.DAY_OF_WEEK)-1; //������ 1 = ��
		if (dayOfWeek==0) dayOfWeek=7; //1=��,...,7=��
		return dayOfWeek;
	}
  
//���������� ��������� ��� �����������
	int getCZ (int year, int month, int day) {
		int m=OCH_MONTH;
		int d=OCH_DAY;
		int w=1;
		if ((m==month) && (d==day)) { numWeek=w; return WEEK_CHIS; }
		if ( (m>month) || (m==month) && (d>day) ) year--;
		leapyear (year);
		int wd=getWeekDay (year,m,d);
		if (wd!=1) { //�������� 1 ������ ��������
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
		numWeek=w; //��������� ���������� ����� ������
		if (w%2==0) return WEEK_ZNAM; 
		else return WEEK_CHIS;
	}

//�������� �� ������� ������
	boolean isVoidString (String s) {
		if (s.trim().length()<1) return true;
		return false;
	}

//������ ���� � ������ � ����� � ��� ��������������� ������ (������, ����, �������� ��� ����)
	void addRes(int day, int i, int c, int hour, int min) {
		Image img = null; // ������ ��������
		if (isVoidString (schedule[day][i][c+1])==false) {
			if (schedule[day][i][c+1].startsWith("*")) img = zTypes[0]; 
			else if (schedule[day][i][c+1].startsWith("!")) img = zTypes[1]; 
			else if (schedule[day][i][c+1].startsWith("#")) img = zTypes[2];
		}
		if (isVoidString (schedule[day][i][c])==false) { // �������� ����
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

//��������� ������ ��������� � ���������� ����
	void prepairRes (int hour, int min) {
		while (lstRes.size()>0) lstRes.delete(0);
		empLastCount=0;
		for (int i=0; i<schedule[dow].length; i++) { // ������� ��� � dayOfWeek
			addRes(dow, i, 2*cz, hour, min);
		}
		while (empLastCount-->0) lstRes.delete(lstRes.size()-1);
		mode = MODE_RES;
		lstRes.setTitle ("���������� ["+shortDays[dow+1]+","+(cz+1)+"�.]");
		display.setCurrent(lstRes);
	}

//��������� �������� �� � ������ ������ ���� �� ����������
	boolean actual(int n, int hour, int min) {
		if (n==1) { // ������ ����
			if ((hour*60+min)<=(call[0][2]*60+call[0][3])) // ������ ���� ��� �� �����������
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

//����������� ����� � ������
	public String oNum(int value) {
		if (value<10) return new String("0"+value); 
		else return new String(""+value);
	}

//��������� ���������� (���������, ������, ����� � �.�.) � ���������� ������ ������ ���������
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
		label.setText (shortDays[dow+1]+", "+ (c==0? "1" : "2")+" ���., "+(selResInd+1) +" ����");
		mode = MODE_DETAILS;
		display.setCurrent(frmRes);
	}

//�������� ������������ ��������� ��������
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
				errorMsg("������! ������ "+(i+1)+" ���� ����� �����: "+oNum(h1)+":"+oNum(m1)+"-"+oNum(h2)+":"+oNum(m2));
				return false;
			}
			if (i>0) {
				if (h1*60+m1 <= pred) {
					int h0 = pred/60;
					int m0 = pred - h0*60;
					errorMsg("������! ������ "+(i+1)+" ���� ������ ����� "+i+": "+oNum(h0)+":"+oNum(m0)+"-"+oNum(h1)+":"+oNum(m1));
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
			errorMsg("���� ������ �� �.�. ������!");
			return false;
		}
		int d=Integer.parseInt(day1Input.getString().trim());
		int m=month1Input.getSelectedIndex();
		if (correctDate (year,d,m)==false) {
			//errorMsg(""+oNum(d)+"."+oNum(m+1)+" ����������� � "+year);
			errorMsg("������������ ���� � ������ ������ ("+oNum(m+1)+"."+year+")");
			return false;
		}    
		if (time1Input.getString().trim().length()<1) {
			errorMsg("���� \"����� �������\" �� ����� ���� ������!");
			return false;
		}
		int t=Integer.parseInt(time1Input.getString().trim());
		if ((t<-12) || (t>12)) {
			errorMsg("��������� �������� ������ ������� �� -12 �� 12 ������������!");
			return false;
		}
		OCH_MONTH = m;
		OCH_DAY = d;
		TIME_SDVIG = t;
		return true;
	}     
 
//�������� ������������ ��������� ���
	boolean correctInput () {
		if (numberInput.getString().trim().length()<1) {
			errorMsg("����� ���� �� �.�. ������!");
			return false;
		}
		int n=Integer.parseInt(numberInput.getString());
		if ((n<1) || (n>PAIRS)) {
			errorMsg("����� ���� �.�. �� 1 �� "+ PAIRS+ "!");
			return false;
		}
		String name=nameInput.getString().trim();
		if (name.length()<1) {
			errorMsg("�������� ���� �� �.�. ������!");
			return false;
		}
		String aud=audInput.getString().trim();
		if (aud.length()<1) {
			errorMsg("��������� �� �.�. ������!");
			return false;
		}
		int numday=weekDayInput.getSelectedIndex();
		boolean w1=weekInput.isSelected(0);
		boolean w2=weekInput.isSelected(1);
		if ((w1==false) && (w2==false)) {
			errorMsg("�������� 1 �/��� 2 ���.!");
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

//����� ��������� �� ������ �� ������� ������
	public void errorMsg (String strError) {
		Alert a = new Alert("������:", strError, null, AlertType.ERROR);
		a.setTimeout(3000);
		display.setCurrent(a);  
	}
 
//������� �� ������� ��������� ������
	public void commandAction(Command c, Displayable d)  {
		if ((c==cmdExitFirst) || (c==cmdExit)) {
			if (changed==true) saveRecords();   
			midlet.exitMIDlet();
		} 
		else if (c==cmdDelete) { //������ �������
			int selResInd = lstRes.getSelectedIndex();
			schedule[dow][selResInd][cz*2]="";
			schedule[dow][selResInd][cz*2+1]="";
			mode = MODE_ACTUAL;
			display.setCurrent(lstActual);
			changed = true;
		}
		else if (c==cmdChange) { //������ ��������
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
		else if (c==cmdDeleteAll) { //������ ������� ���
			display.setCurrent(frmAlert);
		}
		else if (c==confirmOK) { //����������� ���������
			for (int i=0; i<6; i++)
				for (int j=0; j<PAIRS; j++)
					for (int k=0; k<4; k++) schedule[i][j][k]="";
			mode = MODE_ACTUAL;
			display.setCurrent(lstActual);
			changed = true;
		}
		else if (c==confirmCancel) { //�������� ���������
			mode = MODE_ACTUAL;
			display.setCurrent(lstActual);
		}    
		else if (c==cmdBack) { //������ �����
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
		else if (c==List.SELECT_COMMAND) { //����� �� �������� ������
			switch (mode) {
			case MODE_ACTUAL:
				scheduleMode = lstActual.getSelectedIndex();
				switch (scheduleMode) {
				case SCHEDULE_TODAY:
					updateListHeaders();   
					dow = dayOfWeek-1; // 0 = ��
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
					new Message (midlet, lstActual, "������").show ("���������� �������\nv.1.0 (RU)\n\n"
							+ "������� ���� � ����� ������ ������� � ���� \"���������\". "
							+ "��� �� �������� ����� ������ ���. ����� \"���� ����\" ��������� �������� �������. "
							+ "��������� ������� �������� � ������ \"�����������\" (�� ������ ���� �� ������).\n\n"
							+ "(C) Koval (kov3000@ya.ru)"); 
					break;
				}
				break;
			case MODE_DOW:
				dow = lstDOW.getSelectedIndex(); //0 = ��
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
			case (MODE_RES): // ����� ������ �� ���������� ����
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

