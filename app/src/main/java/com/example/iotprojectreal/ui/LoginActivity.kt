package com.example.iotprojectreal.ui

import android.content.Intent
import android.os.Bundle
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.example.android_resapi.ui.MainActivity
import com.example.iotprojectreal.databinding.ActivityLoginBinding
import com.google.firebase.auth.ktx.auth
import com.google.firebase.ktx.Firebase

class LoginActivity : AppCompatActivity() {
    lateinit var binding : ActivityLoginBinding
    override fun onCreate(savedInstanceState : Bundle?){
        super.onCreate(savedInstanceState)
        binding = ActivityLoginBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.login.setOnClickListener {
            val userEmail = binding.username.text.toString()
            val password = binding.password.text.toString()
            doLogin(userEmail, password)
        }

        binding.signup.setOnClickListener {
            startActivity(Intent(this, NewMemberActivity::class.java))
        }

    }

    private fun doLogin(userEmail: String, password: String) {
        Firebase.auth.signInWithEmailAndPassword(userEmail, password)
            .addOnCompleteListener(this) {
                if (it.isSuccessful) {
                    startActivity(
                        Intent(this, MainActivity::class.java).apply {
                            setFlags(Intent.FLAG_ACTIVITY_NEW_TASK or Intent.FLAG_ACTIVITY_CLEAR_TOP)
                            putExtra("id", binding.username.text.toString())
                        })
                    finish()
                } else {
                    Toast.makeText(this, "로그인에 실패하였습니다.", Toast.LENGTH_SHORT).show()
                }
            }
    }
}