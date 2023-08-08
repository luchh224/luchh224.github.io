package com.zybooks.weightlosskcl;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;


//Start of the onClick for transition from Login Screen to Main Screen (MainActivity)
public class LoginActivity extends AppCompatActivity {


    //This is going to create variables to edit text
    private EditText usernameEdt, passwordEdt;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.login_screen);

        //This is going to initialize our variables. Our edit text views are already assigned names
        //and I will use those on the findViewByID method
        usernameEdt = findViewById(R.id.editTextUsername);
        passwordEdt = findViewById(R.id.editTextPassword);


        Button switchToMainActivity;
        Button switchToRegisterActivity;

        // Setting the onClickListener to activate on button press. This will take the user from the Login Activity to the Main Screen
        switchToMainActivity = findViewById(R.id.button_login);
        switchToMainActivity.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                String username = usernameEdt.getText().toString();
                String password = passwordEdt.getText().toString();

                //This is going to be the if statement to check if the fields have all been filled in before proceeding to prevent a login
                //from happening where nothing is filled in
                if (username.isEmpty() && password.isEmpty()) {
                    Toast.makeText(LoginActivity.this, "Please fill in all of the fields", Toast.LENGTH_SHORT).show();
                    return;
                }
                startActivity(new Intent(LoginActivity.this, MainActivity.class));
            }
        });
        // Setting the onClickListener to activate on button press. This will take the user from the Login Activity to the Register Screen.
        // Still need to create database and modify this portion so that the user will not be able to login without proper verification VIA the user database.
        switchToRegisterActivity = findViewById(R.id.button_create_account);
        switchToRegisterActivity.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(LoginActivity.this, RegisterActivity.class));
            }
        });
    }
}