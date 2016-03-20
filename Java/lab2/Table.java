package lab2;

public class Table extends Furniture implements Oak {

	public String color;
	private int num;
	
	@Override
	public void tree() {
		System.out.println("стол #"+num+": тип дерева: "+type);
	}

	@Override
	public void oak() {
		System.out.println("стол #"+num+": цвет дуба: "+color);
	}

	@Override
	public void setColorOfOak(int num, String color) {
		this.color = color;
		this.num = num;
	}

	@Override
	public void setTypeOfTree(int num, String type) {}

}
