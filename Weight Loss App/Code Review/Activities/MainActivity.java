package com.zybooks.weightlosskcl;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;


//Starting the process for the onClick when the Image Button is pressed
public class MainActivity extends AppCompatActivity {
    Button switchToDeleteActivity;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main_screen);

        //Referencing Image Button rather than a normal button like on the login activity
        ImageButton button_delete = (ImageButton) findViewById(R.id.button_delete);
        button_delete.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(getApplicationContext(), "delete button is Clicked", Toast.LENGTH_SHORT).show();
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