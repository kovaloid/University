package lab2;

public class Table extends Furniture implements Oak {

	public String color;
	private int num;
	
	@Override
	public void tree() {
		System.out.println("���� #"+num+": ��� ������: "+type);
	}

	@Override
	public void oak() {
		System.out.println("���� #"+num+": ���� ����: "+color);
	}

	@Override
	public void setColorOfOak(int num, String color) {
		this.color = color;
		this.num = num;
	}

	@Override
	public void setTypeOfTree(int num, String type) {}

}
