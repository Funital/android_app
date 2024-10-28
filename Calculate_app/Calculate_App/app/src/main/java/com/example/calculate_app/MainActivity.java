package com.example.calculate_app;

import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
//        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
//        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
//            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
//            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
//            return insets;
//        });
    }

    int count;

    public void bt_plus_onClick(View v){
        EditText et = findViewById(R.id.et);
        TextView tv = findViewById(R.id.tv);
        int value = Integer.parseInt(et.getText().toString());
        count += value;
        tv.setText(String.valueOf(count));
    }

    public void bt_minus_onClick(View v){
        EditText et = findViewById(R.id.et);
        TextView tv = findViewById(R.id.tv);
        int value = Integer.parseInt(et.getText().toString());
        count -= value;
        tv.setText(String.valueOf(count));
    }
    public void bt_reset_onClick(View v){
        EditText et = findViewById(R.id.et);
        TextView tv = findViewById(R.id.tv);
        count = 0;
        tv.setText(String.valueOf(count));
    }

}