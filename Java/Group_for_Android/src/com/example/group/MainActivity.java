/*
6. Создать приложение для мобильного телефона - список группы с возможностью добавления и удаления, 
которое демонстрирует работу с постоянной памятью - record store.
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

// имена атрибутов для Map
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
	// упаковываем данные в понятную для адаптера структуру
	    data = new ArrayList<Map<String, Object>>();
	// массив имен атрибутов, из которых будут читаться данные
	    String[] from = { ATTRIBUTE_NAME_TEXT, ATTRIBUTE_NAME_IMAGE };
	// массив ID View-компонентов, в которые будут вставляться данные
	    int[] to = { R.id.tvText, R.id.ivImg };
	// создаем адаптер
	    sAdapter = new SimpleAdapter(this, data, R.layout.item, from, to);
	// определяем список и присваиваем ему адаптер
	    lvSimple = (ListView) findViewById(R.id.lvSimple);
	    lvSimple.setAdapter(sAdapter);
	    registerForContextMenu(lvSimple);
	}

	
	public void onButtonClick(View v) {
		
	// создаем новый Map
	    m = new HashMap<String, Object>();
	    m.put(ATTRIBUTE_NAME_TEXT, text.getText().toString());
	    m.put(ATTRIBUTE_NAME_IMAGE, R.drawable.ic_launcher);
	// добавляем его в коллекцию
	    data.add(m);
	// уведомляем, что данные изменились
	    sAdapter.notifyDataSetChanged();
	// очищаем поле ввода
	    text.setText(""); 
	}

	
	@Override
	public void onCreateContextMenu(ContextMenu menu, View v, ContextMenuInfo menuInfo) {
	    super.onCreateContextMenu(menu, v, menuInfo);
	    menu.add(0, CM_DELETE_ID, 0, "Удалить запись");
	}
	

	@Override
	public boolean onContextItemSelected(MenuItem item) {
	    if (item.getItemId() == CM_DELETE_ID) {
		// получаем инфу о пункте списка
		    AdapterContextMenuInfo acmi = (AdapterContextMenuInfo) item.getMenuInfo();
		// удаляем Map из коллекции, используя позицию пункта в списке
		    data.remove(acmi.position);
		// уведомляем, что данные изменились
		    sAdapter.notifyDataSetChanged();
		    return true;
	    }
	    return super.onContextItemSelected(item);
	}
	
}
