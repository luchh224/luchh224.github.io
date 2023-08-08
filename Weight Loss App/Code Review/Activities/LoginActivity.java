package com.zybooks.weightlosskcl;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;


//Start of the onClick for transition from Login Screen to Main Screen (MainActivity)
public class LoginActivity extends AppCompatActivity {
    Button switchToMainActivity;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.login_screen);

        // Setting the onClickListener to activate on button press
        switchToMainActivity = findViewById(R.id.button_login);
        switchToMainActivity.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                switchActivities();
                    switchActivitiesWithData();
            }
        });
    }

    private void switchActivities() {
        Intent switchActivityIntent = new Intent(this, MainActivity.class);
        startActivity(switchActivityIntent);
    }

    //When data is entered into the first page (Username and Password) data should follow with it
    private void switchActivitiesWithData() {
        Intent switchActivityIntent = new Intent(this, MainActivity.class);
        switchActivityIntent.putExtra("message", "from: " + LoginActivity.class.getSimpleName());
        startActivity(switchActivityIntent);
    }
}