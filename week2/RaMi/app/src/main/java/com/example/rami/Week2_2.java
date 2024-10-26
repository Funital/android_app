package com.example.rami;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class Week2_2 extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_week22);
    }

    public void bt_launch_onClick(View v){
//        Ex1
//        TextView tv_helloworld = findViewById(R.id.tv_helloworld);
//        tv_helloworld.setText(R.string.msg_negative);

//        Ex2
//        EditText et_input = findViewById(R.id.et_input);
//        TextView tv_helloworld = findViewById(R.id.tv_helloworld);
//        tv_helloworld.setText(et_input.getText().toString());

//        Ex3
        EditText et_input = findViewById(R.id.et_input);
        TextView tv_helloworld = findViewById(R.id.tv_helloworld);
        tv_helloworld.setText(TextProcessor.Processor(et_input.getText().toString()));
    }
}