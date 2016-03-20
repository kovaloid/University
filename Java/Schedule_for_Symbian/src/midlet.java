/*
7. Создать бизнес-приложение или приложение-игру для мобильного телефона. В отчете необходимо 
наличие титульного листа, диаграмм классов, описания предназначения классов и методов, 
скриншотов и кода приложения в конце.
 */

import javax.microedition.lcdui.*;
import javax.microedition.midlet.*;
import java.util.*;

public class midlet extends MIDlet { 
	
	private boolean isStarted = false;
	private Display display;
	public Timer timer=null;
	public midletTimerTask task=null;
	private midletCanvas canvas;

	public midlet() { 
		display = Display.getDisplay(this);
		canvas  = new midletCanvas(this);
		timer = new Timer();
		task = new midletTimerTask (this,canvas);
		timer.scheduleAtFixedRate(task,1000,1000);
	}

	protected void startApp() {
		if (isStarted) { return; }
		display.setCurrent(canvas);
		isStarted = true;
	}

	protected void pauseApp()  { }

	protected void destroyApp( boolean unconditional )  { }
 
	public void exitMIDlet()  {
		System.gc();
		destroyApp(true);
		notifyDestroyed();
	}

	public void start()  {
		if (task != null) {
			task.cancel();
			task = null;
		}
		if (timer != null) {
			timer.cancel();
			timer = null;
		}
		new Schedule (this);
	}

}    
           