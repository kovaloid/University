import javax.microedition.lcdui.*;

public class Message extends Form implements CommandListener {
	
	StringItem label;
	midlet midlet;
	Displayable parent;
	Command cmdBack;

	public Message (midlet midlet, Displayable parent, String hdr) {
		super (hdr);
		this.midlet = midlet;
		this.parent = parent;
		label = new StringItem ("", "");
		append (label);
		cmdBack = new Command("Назад", Command.BACK, 1);
		addCommand (cmdBack);
	}

	public void show (String s) {
		label.setText (s);
		Display.getDisplay(midlet).setCurrent (this);
		setCommandListener (this);
	}

	public void commandAction (Command c, Displayable d) {
		Display.getDisplay(midlet).setCurrent(parent);
	}

}