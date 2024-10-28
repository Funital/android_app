package com.example.layout_practice;

import android.os.Bundle;
import android.os.SystemClock;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import java.util.Random;

public class MainActivity extends AppCompatActivity {

    Random rand = new Random();
    long startTime;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
        // 시작 시간을 초기화
        startTime = SystemClock.elapsedRealtime();
    }

    public void bt_launch_onClick(View v){
        FrameLayout layout = findViewById(R.id.layout);
        TextView textView = findViewById(R.id.tv); // 시간 표시할 TextView

        Button bt = new Button(this);

        FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(
                150,
                150);

        v.setVisibility(View.INVISIBLE);
        // 버튼이 생성되는 순간의 시간 저장
        startTime = System.nanoTime();

        bt.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Button bt_launch = findViewById(R.id.bt_launch);
                bt_launch.setVisibility(View.VISIBLE);
                v.setVisibility(View.INVISIBLE);

                // 현재 시간과 시작 시간의 차이를 나노초 단위로 계산
                long elapsedNanoSeconds = System.nanoTime() - startTime;

                // 초 단위로 변환하여 TextView에 표시
                double elapsedSeconds = elapsedNanoSeconds / 1_000_000_000.0;
                textView.setText("경과 시간: " + elapsedSeconds + "초");
            }
        });

        params.leftMargin = rand.nextInt(layout.getMeasuredWidth()-150);
        params.topMargin = rand.nextInt(layout.getMeasuredHeight()-150);

        layout.addView(bt, params);

    }
}