package com.example.iotprojectreal.ui

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.example.iotprojectreal.databinding.ActivityAttdBinding


class AttdActivity : AppCompatActivity() {
    lateinit var binding : ActivityAttdBinding
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityAttdBinding.inflate(layoutInflater)
        setContentView(binding.root)


    }
}