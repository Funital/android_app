package com.example.icecream;

import android.os.Bundle;
import android.view.View;
import android.widget.CheckBox;
import android.widget.ProgressBar;
import android.widget.TextView;

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

        Calculate();
    }

    void Calculate(){
        CheckBox cb_almond = findViewById(R.id.cb_almond);
        CheckBox cb_choco = findViewById(R.id.cb_choco);
        CheckBox cb_banana = findViewById(R.id.cb_banana);

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

        TextView tv_calories = findViewById(R.id.tv_calories);
        ProgressBar pb_calories = findViewById(R.id.pb_calories);

        tv_calories.setText(calories + "kcal");
        pb_calories.setProgress(calories);
    }
    public void onClick(View v){
        Calculate();
    }
}