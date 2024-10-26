package com.example.icecream;

import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.RadioButton;
import android.widget.TextView;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import java.security.PublicKey;

public class MainActivity extends AppCompatActivity {

    int calories;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        EditText et_syrupyang = findViewById(R.id.et_syrupyang);
        et_syrupyang.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                Calculate();
            }
        });

        Calculate();
    }

    void Calculate(){
        CheckBox cb_almond = findViewById(R.id.cb_almond);
        CheckBox cb_choco = findViewById(R.id.cb_choco);
        CheckBox cb_banana = findViewById(R.id.cb_banana);

        RadioButton rb_chocoIce = findViewById(R.id.rb_chocoIce);
        RadioButton rb_vanilla = findViewById(R.id.rb_vanilla);
        RadioButton rb_yogurt = findViewById(R.id.rb_yogurt);

        EditText et_syrupyang = findViewById(R.id.et_syrupyang);

        calories = 0;
        if (cb_choco.isChecked()){
            calories += 200;
        }
        if (cb_almond.isChecked()){
            calories += 100;
        }
        if (cb_banana.isChecked()){
            calories += 50;
        }
        if (rb_chocoIce.isChecked()){
            calories += 1000;
        }
        if (rb_vanilla.isChecked()){
            calories += 1200;
        }
        if (rb_yogurt.isChecked()){
            calories += 1500;
        }

        int syrupyang = Integer.parseInt(et_syrupyang.getText().toString());
        calories += syrupyang * 2;

        TextView tv_calories = findViewById(R.id.tv_calories);
        ProgressBar pb_calories = findViewById(R.id.pb_calories);

        tv_calories.setText(calories + "kcal");
        pb_calories.setProgress(calories);
    }
    public void onClick(View v){
        Calculate();
    }

    public void bt_launch_onClick(View v){
        if (calories > 3000){
            Toast.makeText(this, "당신은 너무 많이 먹어 배가 터졌습니다.", Toast.LENGTH_SHORT).show();
        }else{
            Toast.makeText(this, "주문이 완료되었습니다!", Toast.LENGTH_SHORT).show();
        }
    }
}