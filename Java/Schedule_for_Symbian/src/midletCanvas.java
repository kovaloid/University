import javax.microedition.lcdui.*;

class midletCanvas extends Canvas {
	
	public midlet midlet;
	public boolean clearDisplay = true, textOn=false;
	private int bkColor=0x000000, //фон экрана
				textColor=0xFFFFFF; //цвет надписи
	public Image p0 = null;
	private int cx,cy,color;
	private Font font;

	public midletCanvas (midlet midlet) {
		this.midlet = midlet;
		cx=getWidth()/2;
		cy=getHeight()/2;
		try { 
			p0 = Image.createImage("/start.png");
		}
		catch (java.io.IOException e) {}
		font = Font.getFont (Font.FACE_SYSTEM, Font.STYLE_PLAIN, Font.SIZE_SMALL);
	}
 
	public void reDraw (Graphics g) {
		if (textOn==true) { color=bkColor; textOn=false; }
		else { color=textColor; textOn=true; }
		g.setColor(color);
		g.setFont (font);
		g.drawString("Нажмите на экран...",cx,getHeight()-2-font.getHeight(),Graphics.HCENTER|Graphics.TOP);
	}    
 
	protected void paint(Graphics g) {    
		if (clearDisplay) {
			g.setColor (bkColor);
			g.fillRect(0,0,getWidth(),getHeight());
			g.drawImage(p0,cx,cy,Graphics.HCENTER|Graphics.VCENTER);
		}
		reDraw (g);
		clearDisplay = false;
	}
    
	public void keyPressed(int keyCode) {
			midlet.start ();
	}
	
	protected void pointerPressed(int x, int y) {
			midlet.start ();
	}

}
