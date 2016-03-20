/*
6. ������� ���������� ��� ���������� �������� - ������ ������ � ������������ ���������� � ��������, 
������� ������������� ������ � ���������� ������� - record store.
*/

package com.example.group;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import android.app.Activity;
import android.os.Bundle;
import android.view.ContextMenu;
import android.view.ContextMenu.ContextMenuInfo;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView.AdapterContextMenuInfo;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;

public class MainActivity extends Activity {

	private static final int CM_DELETE_ID = 1;

// ����� ��������� ��� Map
	final String ATTRIBUTE_NAME_TEXT = "text";
	final String ATTRIBUTE_NAME_IMAGE = "image";
	
	ListView lvSimple;
	SimpleAdapter sAdapter;
	ArrayList<Map<String, Object>> data;
	Map<String, Object> m;
	TextView text1;
	EditText text;
	Button del;

	
	/** Called when the activity is first created. */
	public void onCreate(Bundle savedInstanceState) {
	    super.onCreate(savedInstanceState);
	    setContentView(R.layout.activity_main);
	    text = (EditText) findViewById(R.id.start);
	    del = (Button) findViewById(R.id.Button2);
	    OnClickListener oclDel = new OnClickListener() {
	    	@Override
	    	public void onClick(View v) {
	    	    data.clear();
	    	    sAdapter.notifyDataSetChanged();
	    	}
	    };
	    del.setOnClickListener(oclDel);
	// ����������� ������ � �������� ��� �������� ���������
	    data = new ArrayList<Map<String, Object>>();
	// ������ ���� ���������, �� ������� ����� �������� ������
	    String[] from = { ATTRIBUTE_NAME_TEXT, ATTRIBUTE_NAME_IMAGE };
	// ������ ID View-�����������, � ������� ����� ����������� ������
	    int[] to = { R.id.tvText, R.id.ivImg };
	// ������� �������
	    sAdapter = new SimpleAdapter(this, data, R.layout.item, from, to);
	// ���������� ������ � ����������� ��� �������
	    lvSimple = (ListView) findViewById(R.id.lvSimple);
	    lvSimple.setAdapter(sAdapter);
	    registerForContextMenu(lvSimple);
	}

	
	public void onButtonClick(View v) {
		
	// ������� ����� Map
	    m = new HashMap<String, Object>();
	    m.put(ATTRIBUTE_NAME_TEXT, text.getText().toString());
	    m.put(ATTRIBUTE_NAME_IMAGE, R.drawable.ic_launcher);
	// ��������� ��� � ���������
	    data.add(m);
	// ����������, ��� ������ ����������
	    sAdapter.notifyDataSetChanged();
	// ������� ���� �����
	    text.setText(""); 
	}

	
	@Override
	public void onCreateContextMenu(ContextMenu menu, View v, ContextMenuInfo menuInfo) {
	    super.onCreateContextMenu(menu, v, menuInfo);
	    menu.add(0, CM_DELETE_ID, 0, "������� ������");
	}
	

	@Override
	public boolean onContextItemSelected(MenuItem item) {
	    if (item.getItemId() == CM_DELETE_ID) {
		// �������� ���� � ������ ������
		    AdapterContextMenuInfo acmi = (AdapterContextMenuInfo) item.getMenuInfo();
		// ������� Map �� ���������, ��������� ������� ������ � ������
		    data.remove(acmi.position);
		// ����������, ��� ������ ����������
		    sAdapter.notifyDataSetChanged();
		    return true;
	    }
	    return super.onContextItemSelected(item);
	}
	
}
