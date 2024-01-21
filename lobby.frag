// Параметры виньетки
uniform float vignetteAmount; // Сила виньетки, от 0 до 1
uniform float vignetteRadius; // Радиус виньетки, от 0 до 1
uniform vec4 vignetteColor; // Цвет виньетки, в формате RGBA

// Функция, которая вычисляет расстояние от центра до текущего пикселя
float distanceToCenter(vec2 uv) {
  vec2 center = vec2(0.5, 0.5); // Координаты центра
  return distance(uv, center); // Расстояние между двумя точками
}

// Функция, которая возвращает цвет пикселя с применением виньетки
vec4 applyVignette(vec4 color, vec2 uv) {
  float dist = distanceToCenter(uv); // Расстояние от центра
  float factor = smoothstep(vignetteRadius, vignetteRadius - vignetteAmount, dist); // Коэффициент затемнения, от 0 до 1
  return mix(vignetteColor, color, factor); // Смешивание цветов по коэффициенту
}

// Основная функция шейдера, которая возвращает цвет фрагмента
void main() {
  vec4 color = texture2D(_MainTex, v2f_texcoord); // Цвет пикселя из текстуры
  vec2 uv = v2f_texcoord.xy; // Координаты пикселя
  gl_FragColor = applyVignette(color, uv); // Применение виньетки
}
