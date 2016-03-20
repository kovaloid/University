import java.util.TimerTask;

class midletTimerTask extends TimerTask {
	
	private midletCanvas canvas;
	private midlet midlet;
	private int sec;
    
	public midletTimerTask (midlet midlet, midletCanvas canvas) {
		this.canvas = canvas;
		this.midlet = midlet;
		sec=0;
	}

	public final void run() {  
		sec++;
		if (sec<20) canvas.repaint();
		else midlet.start ();
	}
	
}
