# Inserção de Dados de Sensores com ESP32 em um Bucket Amazon S3

Este projeto demonstra como inserir dados de sensores com um ESP32 em um bucket no Amazon S3 e exibi-los em uma página web.

## Sumário

- [Pré-requisitos](#pré-requisitos)
- [Hardware Necessário](#hardware-necessário)
- [Configuração](#configuração)
- [Bucket Policy](#bucket-policy)
- [CORS Configuration](#cors-configuration)

## Pré-requisitos

- Conta na Amazon Web Services (AWS)
- Bucket criado no Amazon S3
- Credenciais de rede Wi-Fi

## Hardware Necessário

- ESP32
- Sensor analógico (p.ex., sensor de som)
- Cabos de conexão

## Configuração

1. Configure seu bucket no Amazon S3 e obtenha a URL do bucket.
2. Configure as credenciais da sua rede Wi-Fi.

## CORS Configuration

Nas permissões do bucket adicione a seguinte configuração CORS ao seu bucket S3 para permitir solicitações de origem cruzada.
Substitua http://127.0.0.1:5500 conforme as informações da sua máquina

```json
[
  {
    "AllowedOrigins": ["http://127.0.0.1:5500"],
    "AllowedMethods": ["GET"],
    "MaxAgeSeconds": 3000,
    "AllowedHeaders": ["*"]
  }
]
```

## Bucket Policy

Nas permissões do bucket adicione a seguinte política ao seu bucket S3 para permitir leitura e escrita pública:

```json
{
    "Version": "2012-10-17",
    "Statement": [
        {
            "Sid": "PublicReadGetObject",
            "Effect": "Allow",
            "Principal": "*",
            "Action": "s3:GetObject",
            "Resource": "arn:aws:s3:::esp32dados/*"
        },
        {
            "Sid": "PublicWritePutObject",
            "Effect": "Allow",
            "Principal": "*",
            "Action": "s3:PutObject",
            "Resource": "arn:aws:s3:::esp32dados/*"
        }
    ]
}
