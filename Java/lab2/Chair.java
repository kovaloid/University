package lab2;

public class Chair extends Furniture implements Tree{

	private String type;
	private int num;
	
	@Override
	public void tree() {
		System.out.println("���� #"+num+": ��� ������: "+type);
	}

	@Override
	public void setTypeOfTree(int num, String type) {
		this.type = type;
		this.num = num;
	}

}
