package com.zybooks.weightlosskcl;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class GoalActivity extends AppCompatActivity {

    Button switchToMainActivity;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.goal_screen);

        //Referencing Image Button rather than a normal button like on the login activity. This takes you
        //back to main screen
        switchToMainActivity = findViewById(R.id.goalWeight_cancelButton);
        switchToMainActivity.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(GoalActivity.this, MainActivity.class));
            }
        });

        //Referencing Image Button rather than a normal button like on the login activity. This takes you
        //back to main screen and also prompts user that the goal weight has been set VIA Toast
        switchToMainActivity = findViewById(R.id.goalWeight_saveButton);
        switchToMainActivity.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(GoalActivity.this, MainActivity.class));
                Toast.makeText(GoalActivity.this, "Your Goal Weight Has Been Set! Good Luck!", Toast.LENGTH_SHORT).show();
            }
        });
    }
}
