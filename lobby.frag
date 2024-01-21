// ��������� ��������
uniform float vignetteAmount; // ���� ��������, �� 0 �� 1
uniform float vignetteRadius; // ������ ��������, �� 0 �� 1
uniform vec4 vignetteColor; // ���� ��������, � ������� RGBA

// �������, ������� ��������� ���������� �� ������ �� �������� �������
float distanceToCenter(vec2 uv) {
  vec2 center = vec2(0.5, 0.5); // ���������� ������
  return distance(uv, center); // ���������� ����� ����� �������
}

// �������, ������� ���������� ���� ������� � ����������� ��������
vec4 applyVignette(vec4 color, vec2 uv) {
  float dist = distanceToCenter(uv); // ���������� �� ������
  float factor = smoothstep(vignetteRadius, vignetteRadius - vignetteAmount, dist); // ����������� ����������, �� 0 �� 1
  return mix(vignetteColor, color, factor); // ���������� ������ �� ������������
}

// �������� ������� �������, ������� ���������� ���� ���������
void main() {
  vec4 color = texture2D(_MainTex, v2f_texcoord); // ���� ������� �� ��������
  vec2 uv = v2f_texcoord.xy; // ���������� �������
  gl_FragColor = applyVignette(color, uv); // ���������� ��������
}
