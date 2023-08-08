package com.zybooks.weightlosskcl;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.media.Image;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;


//Starting the process for the onClick when the Image Button is pressed
public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main_screen);

        //Referencing Image Button rather than a normal button like on the login activity. This takes you
        //to the delete weight screen
        ImageButton button_delete = (ImageButton) findViewById(R.id.button_delete);
        button_delete.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this, DeleteActivity.class));
            }
        });
        //Referencing Image Button rather than a normal button like on the login activity. This takes you
        //to the change weight screen
        ImageButton change_button = (ImageButton) findViewById(R.id.change_button);
        change_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this, ChangeActivity.class));
            }
        });
        //Referencing Image Button rather than a normal button like on the login activity. This takes you
        //to the add weight screen
        ImageButton add_button = (ImageButton) findViewById(R.id.add_button);
        add_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this, AddActivity.class));
            }
        });
        //Referencing Image Button rather than a normal button like on the login activity. This takes you
        //to the goal weight screen
        ImageButton set_button = (ImageButton) findViewById(R.id.set_button);
        set_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this, GoalActivity.class));
            }
        });
    }

    private void switchActivities() {
        Intent switchActivityIntent = new Intent(this, DeleteActivity.class);
        startActivity(switchActivityIntent);
    }

    private void switchActivitiesWithData() {
        Intent switchActivityIntent = new Intent(this, DeleteActivity.class);
        switchActivityIntent.putExtra("message", "from: " + MainActivity.class.getSimpleName());
        startActivity(switchActivityIntent);
        
    }
}